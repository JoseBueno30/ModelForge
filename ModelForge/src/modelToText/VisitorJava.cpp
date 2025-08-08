#include <filesystem>
#include <iostream>
#include <modelToText/VisitorJava.h>



namespace ModelToText {

std::string VisitorJava::visibilityToString(MetaModel::Visibility vis) {
    switch (vis) {
    case MetaModel::Visibility::Public:    return "public";
    case MetaModel::Visibility::Private:   return "private";
    case MetaModel::Visibility::Protected: return "protected";
    case MetaModel::Visibility::Package:   return "package";
    }
    return "";
}

std::string VisitorJava::simpleTypeToJavaString(const MetaModel::SimpleType& type) {
    if (dynamic_cast<const MetaModel::String*>(&type)) {
        return "String";
    } else if (dynamic_cast<const MetaModel::Integer*>(&type)) {
        return "Integer";
    } else if (dynamic_cast<const MetaModel::Real*>(&type)){
        return "Double";
    } else if (dynamic_cast<const MetaModel::Boolean*>(&type)) {
        return "Boolean";
    } else if (dynamic_cast<const MetaModel::Void*>(&type)) {
        return "void";
    } else {
        return "Object";
    }
}

VisitorJava::VisitorJava(const std::string& directoryPath) {
    this->directoryPath = directoryPath;
}

VisitorJava::~VisitorJava() {}

std::any VisitorJava::visit(const MetaModel::MetaModel& metaModel) {
    packageName = metaModel.getName();
    std::transform(packageName.begin(), packageName.end(), packageName.begin(), ::tolower);

    this->directoryPath = this->directoryPath + "/java/" + packageName;

    std::filesystem::path javaDir(this->directoryPath);

    std::error_code ec;
    if (!std::filesystem::exists(javaDir)) {
        if (!std::filesystem::create_directories(javaDir, ec)) {
            throw std::runtime_error("Failed to create directory: " + javaDir.string() + ", error: " + ec.message());
        }
    }

    this->metaClasses = &metaModel.getClasses();

    // Visit enums
    for (const auto &metaEnumPair : metaModel.getEnums()) {
        metaEnumPair.second->accept(*this);
    }

    // Visit all classes
    for (const auto &metaClassPair: metaModel.getClasses()) {
        metaClassPair.second->accept(*this);
    }

    // Visit all associations
    for(const auto &metaAssociationPair : metaModel.getAssociations()){
        metaAssociationPair.second->accept(*this);
    }

    // Visit all association classes
    for(const auto &metaAssociationClassPair : metaModel.getAssociationClasses()){
        metaAssociationClassPair.second->accept(*this);
    }

    return 0;
}

std::any VisitorJava::visit(const MetaModel::MetaEnum& metaEnum) {
    std::string filePath = this->directoryPath + "/" + metaEnum.getName() + ".java";
    std::ofstream outFile(filePath);

    outFile << "package " << packageName << ";\n";

    outFile << "public enum " << metaEnum.getName() << " {\n";
    for(const auto &metaEnumPair: metaEnum.getElements()){
        outFile << "\t" << metaEnumPair.second->getName() << ",\n";
    }
    outFile << "}\n";
    outFile.close();

    return 0;
}


std::string VisitorJava::generateClassConstructor(const MetaModel::MetaClass& metaClass, const std::vector<JavaMemberCode> members){
    std::string constructor = "";

    constructor += "\tpublic " + metaClass.getName() + "(";

    bool first = true;
    for (const auto& member : members) {
        if (!member.paramDeclaration.empty()){
            if (!first) constructor += ", ";
            constructor += member.paramDeclaration;
            first = false;
        }
    }
    constructor += ") {\n";

    for (const auto& member : members) {
        constructor += member.paramSet;
    }

    constructor += "\t}\n\n";

    return constructor;
}


std::any VisitorJava::visit(const MetaModel::MetaClass& metaClass) {
    std::string filePath = this->directoryPath + "/" + metaClass.getName() + ".java";
    outFile.open(filePath);

    outFile << "package " << packageName << ";\n";

    std::string classString = "";

    classString += "public";

    if (metaClass.getIsAbstract()){
        classString += " abstract ";
    } else {
        classString += " ";
    }

    classString += "class " + metaClass.getName();

    currentClassImports.clear();

    // TODO: improve inheritance, check before generating if is a java valid model, check if class has no attributes to be an interface else an extension
    auto superClasses = metaClass.getSuperClasses();
    if (!superClasses.empty()) {
        classString += " extends ";
        bool first = true;
        for (const auto &superClassPair : superClasses) {
            if (!first) classString += ", ";
            classString += superClassPair.second->getName();
            first = false;
            break; // only support single inheritance in Java
        }
    }

    classString += "{\n\n";

    std::vector<JavaMemberCode> members;

    //attributes
    for(const auto &attributePair : metaClass.getAttributes()){
        members.push_back(std::any_cast<JavaMemberCode>(attributePair.second->accept(*this)));
    }

    //associations

    for(const auto &assocEndPair: metaClass.getAssociationEnds()){
        members.push_back(std::any_cast<JavaMemberCode>(assocEndPair.second->accept(*this)));
    }

    for (const auto& member : members) {
        classString += member.field;
    }
    classString += "\n";

    classString += generateClassConstructor(metaClass, members);

    for (const auto& member : members) {
        classString += member.getter;
        classString += member.setter;

        if (!member.adder.empty()) {
            classString += member.adder;
        }

        if (!member.remover.empty()) {
            classString += member.remover;
        }
    }

    classString += "}\n";


    for(const auto& import : currentClassImports){
        outFile << "import " + import + ";\n";
    }

    outFile << "\n";

    outFile << classString;

    outFile.close();

    return 0;
}

std::any VisitorJava::visit(const MetaModel::SimpleType& simpleType) {

    if (const MetaModel::MetaClass* metaClassPtr = dynamic_cast<const MetaModel::MetaClass*>(&simpleType)) {
        return metaClassPtr->getName();
    }

    if (const MetaModel::MetaEnum* metaEnumPtr = dynamic_cast<const MetaModel::MetaEnum*>(&simpleType)) {
        return metaEnumPtr->getName();
    }

    return simpleTypeToJavaString(simpleType);
}

std::any VisitorJava::visit(const MetaModel::CollectionType& collectionType) {
    std::string collectionTypeStr = "";

    std::string elementType = std::any_cast<std::string>(collectionType.getType().accept(*this));

    if (collectionType.getIsOrdered() && !collectionType.getIsUnique()) {
        currentClassImports.insert("java.util.List");
        currentClassImports.insert("java.util.ArrayList");
        collectionTypeStr = "List<" + elementType + ">";
    } else if (!collectionType.getIsOrdered() && collectionType.getIsUnique()) {
        currentClassImports.insert("java.util.Set");
        currentClassImports.insert("java.util.HashSet");
        collectionTypeStr = "Set<" + elementType + ">";
    } else if (collectionType.getIsOrdered() && collectionType.getIsUnique()) {
        currentClassImports.insert("java.util.SortedSet");
        currentClassImports.insert("java.util.TreeSet");
        collectionTypeStr = "SortedSet<" + elementType + ">";
    } else {
        currentClassImports.insert("java.util.List");
        currentClassImports.insert("java.util.ArrayList");
        collectionTypeStr = "List<" + elementType + ">";
    }

    return collectionTypeStr;
}

std::any VisitorJava::visit(const MetaModel::TupleType& tupleType) {

    return "TODO TUPLES";
}

std::any VisitorJava::visit(const MetaModel::MetaAssociation& metaAssociation) {
    return 0;
}


std::any VisitorJava::visit(const MetaModel::MetaAssociationClass& metaAssociationClass) {
    return 0;
}

std::any VisitorJava::visitType(const MetaModel::MetaType& metaType){
    if (const auto* simpleType = dynamic_cast<const MetaModel::SimpleType*>(&metaType)) {
        return visit(*simpleType);
    } else {
        return metaType.accept(*this);
    }
}

std::string VisitorJava::capitalize(const std::string& name) {
    if (name.empty()) return name;
    std::string capitalized = name;
    capitalized[0] = std::toupper(capitalized[0]);
    return capitalized;
}

std::any VisitorJava::visit(const MetaModel::MetaAttribute& metaAttribute) {
    JavaMemberCode member;

    member.name = metaAttribute.getName();
    member.type = std::any_cast<std::string>(visitType(metaAttribute.getType()));
    std::string capitalizedName = capitalize(member.name);
    std::string visibility = visibilityToString(metaAttribute.getVisibility());

    member.field = "\tprivate " + member.type + " " + member.name + ";\n";

    member.paramDeclaration = member.type + " " + member.name;

    member.paramSet = "\t\tthis.set" + capitalizedName + "(" + member.name + ");\n";

    member.getter = "\t" + visibility + " " + member.type + " get" + capitalizedName + "() {\n" +
                  "\t\treturn this." + member.name + ";\n" +
                  "\t}\n\n";

    member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + member.type + " " + member.name + ") {\n" +
                  "\t\tthis." + member.name + " = " + member.name + ";\n" +
                  "\t}\n\n";

    if (const auto* collectionType = dynamic_cast<const MetaModel::CollectionType*>(&(metaAttribute.getType()))) {
        std::string elementType = std::any_cast<std::string>(collectionType->getType().accept(*this));
        std::string singularName = (member.name.size() > 1 && member.name.substr(member.name.size() - 1) == "s") ?
                                       member.name.substr(0, member.name.size() - 1) : member.name;

        std::string addName = "add" + capitalize(singularName);
        std::string removeName = "remove" + capitalize(singularName);
        std::string collectionVar = member.name;

        if (member.type.find("List") != std::string::npos) {
            member.paramDeclaration = "";
            member.paramSet = "\t\tthis." + collectionVar + " = new ArrayList<>();\n";
            currentClassImports.insert("java.util.ArrayList");
        } else if (member.type.find("Set") != std::string::npos) {
            member.paramDeclaration = "";
            member.paramSet = "\t\tthis." + collectionVar + " = new HashSet<>();\n";
            currentClassImports.insert("java.util.HashSet");
        } else {
            member.paramDeclaration = "";
            member.paramSet = "\t\tthis." + collectionVar + " = new ArrayList<>();\n";
            currentClassImports.insert("java.util.ArrayList");
        }

        member.adder = "\t" + visibility + " void " + addName + "(" + elementType + " element) {\n" +
                       "\t\tthis." + collectionVar + ".add(element);\n" +
                       "\t}\n\n";

        member.remover = "\t" + visibility + " void " + removeName + "(" + elementType + " element) {\n" +
                         "\t\tthis." + collectionVar + ".remove(element);\n" +
                         "\t}\n\n";
    }

    return member;
}


std::any VisitorJava::visit(const MetaModel::MetaOperation& metaOperation) {
    return 0;
}


std::any VisitorJava::visit(const MetaModel::MetaConstraint& metaConstraint) {
    return 0;
}


std::any VisitorJava::visit(const MetaModel::MetaAssociationEnd& metaAssociationEnd) {
    JavaMemberCode member;

    if (!metaAssociationEnd.getIsNavigable()) return member;

    member.name = metaAssociationEnd.getRole();
    std::string capitalizedName = capitalize(member.name);
    std::string visibility = visibilityToString(metaAssociationEnd.getVisibility());

    std::string targetType = metaAssociationEnd.getClass().getName();

    const MetaModel::MetaMultiplicity& multiplicity = metaAssociationEnd.getMultiplicity();
    int lowerBound = multiplicity.getRanges().empty() ? 1 : multiplicity.getRanges().front()->getLowerBound();
    int upperBound = multiplicity.getRanges().empty() ? 1 : multiplicity.getRanges().front()->getUpperBound();

    bool isMultiple = (upperBound == -1 || upperBound > 1);

    std::string collectionType = "List<" + targetType + ">";
    std::string implementationType = "ArrayList<" + targetType + ">";

    if (isMultiple) {
        currentClassImports.insert("java.util.List");
        currentClassImports.insert("java.util.ArrayList");
        currentClassImports.insert("java.util.Collections");

        member.type = collectionType;
        member.field = "\tprivate " + collectionType + " " + member.name + ";\n";

        std::string singularName = (member.name.back() == 's') ? member.name.substr(0, member.name.size() - 1) : member.name;

        member.getter = "\t" + visibility + " " + collectionType + " get" + capitalizedName + "() {\n" +
                        "\t\treturn Collections.unmodifiableList(this." + member.name + ");\n" +
                        "\t}\n\n";

        if ((lowerBound == upperBound && upperBound > 1) || lowerBound > 1) {
            member.paramDeclaration = collectionType + " " + member.name;
            member.paramSet = "\t\tthis.set" + capitalizedName + "(" + member.name + ");\n";

            member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + collectionType + " " + member.name + ") {\n" +
                            "\t\tif (" + member.name + ".size() < " + std::to_string(lowerBound) +
                            (upperBound != -1 ? " || " + member.name + ".size() > " + std::to_string(upperBound) : "") + ") {\n" +
                            "\t\t\tthrow new IllegalArgumentException(\"Collection must contain " +
                            (upperBound != -1 && upperBound == lowerBound
                                 ? "exactly " + std::to_string(upperBound)
                                 : "at least " + std::to_string(lowerBound) +
                                       (upperBound != -1 ? " and at most " + std::to_string(upperBound) : "")) +
                            " elements.\");\n" +
                            "\t\t}\n" +
                            "\t\tthis." + member.name + " = new " + implementationType + "(" + member.name + ");\n" +
                            "\t}\n\n";

        } else if (lowerBound == 1 && (upperBound == -1 || upperBound > 1)) {
            std::string paramName = singularName;
            member.paramDeclaration = targetType + " " + paramName;
            member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "(" + (upperBound==-1 ? "" : " " + std::to_string(upperBound) + " " ) + ");\n" +
                              "\t\tthis." + member.name + ".add(" + paramName + ");\n";

            member.adder = "\t" + visibility + " void add" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                           "\t\tthis." + member.name + ".add(element);\n" +
                           "\t}\n\n";

            member.remover = "\t" + visibility + " void remove" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                             "\t\tthis." + member.name + ".remove(element);\n" +
                             "\t}\n\n";

            member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + collectionType + " " + member.name + ") {\n" +
                            "\t\tthis." + member.name + " = new " + implementationType + "(" + member.name + ");\n" +
                            "\t}\n\n";

        } else {
            member.paramDeclaration = "";
            member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "();\n";

            member.adder = "\t" + visibility + " void add" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                           "\t\tthis." + member.name + ".add(element);\n" +
                           "\t}\n\n";

            member.remover = "\t" + visibility + " void remove" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                             "\t\tthis." + member.name + ".remove(element);\n" +
                             "\t}\n\n";

            member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + collectionType + " " + member.name + ") {\n" +
                            "\t\tthis." + member.name + " = new " + implementationType + "(" + member.name + ");\n" +
                            "\t}\n\n";
        }

    } else {
        member.type = targetType;
        member.field = "\tprivate " + targetType + " " + member.name + ";\n";
        member.paramDeclaration = targetType + " " + member.name;
        member.paramSet = "\t\tthis.set" + capitalizedName + "(" + member.name + ");\n";

        member.getter = "\t" + visibility + " " + targetType + " get" + capitalizedName + "() {\n" +
                        "\t\treturn this." + member.name + ";\n" +
                        "\t}\n\n";

        member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + targetType + " " + member.name + ") {\n";

        if(lowerBound == 1){
            member.setter += "\t\tif (" + member.name + " == null) {\n" +
                             "\t\t\tthrow new IllegalArgumentException(\"" + member.name + " must not be null.\");\n\t\t}\n";
        }

        member.setter += "\t\tthis." + member.name + " = " + member.name + ";\n\t}\n\n";
    }

    return member;
}


}
