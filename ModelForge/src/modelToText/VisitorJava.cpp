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
        return "string";
    } else if (dynamic_cast<const MetaModel::Integer*>(&type)) {
        return "int";
    } else if (dynamic_cast<const MetaModel::Real*>(&type)){
        return "double";
    } else if (dynamic_cast<const MetaModel::Boolean*>(&type)) {
        return "boolean";
    } else if (dynamic_cast<const MetaModel::Void*>(&type)) {
        return "void";
    } else {
        return "null";
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


std::string generateClassConstructor(const MetaModel::MetaClass& metaClass){
    std::string constructor = "";

    constructor += "public " + metaClass.getName() + "(";

    bool first = true;
    for (const auto& attributePair : metaClass.getAttributes()) {
        if (!first) constructor += ", ";


        first = false;
    }
    constructor += ") {\n";


    constructor += "\t}\n\n";

    return constructor;
}


std::any VisitorJava::visit(const MetaModel::MetaClass& metaClass) {
    std::string filePath = this->directoryPath + "/" + metaClass.getName() + ".java";
    outFile.open(filePath);

    outFile << "package " << packageName << ";\n";

    outFile << "public" << (metaClass.getIsAbstract() ? " abstract " : " ") << "class " << metaClass.getName();

    currentClassImports.clear();

    // TODO: improve inheritance, check before generating if is a java valid model, check if class has no attributes to be an interface else an extension
    auto superClasses = metaClass.getSuperClasses();
    if (!superClasses.empty()) {
        outFile << " extends ";
        bool first = true;
        for (const auto &superClassPair : superClasses) {
            if (!first) outFile << ", ";
            outFile << superClassPair.second->getName();
            first = false;
            break; // only support single inheritance in Java
        }
    }

    outFile << "{\n\n";

    std::vector<JavaMemberCode> members;

    //attributes
    for(const auto &attributePair : metaClass.getAttributes()){
        members.push_back(std::any_cast<JavaMemberCode>(attributePair.second->accept(*this)));
    }

    for (const auto& member : members) {
        outFile << member.field;
    }
    outFile << "\n";

    outFile << generateClassConstructor(metaClass);

    for (const auto& member : members) {
        outFile << member.getter;
        outFile << member.setter;

        if (!member.adder.empty()) {
            outFile << member.adder;
        }

        if (!member.remover.empty()) {
            outFile << member.remover;
        }
    }

    outFile << "}\n";
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


std::any VisitorJava::visit(const MetaModel::MetaAssociationEnd& metaAssociatonEnd) {
    return 0;
}


}
