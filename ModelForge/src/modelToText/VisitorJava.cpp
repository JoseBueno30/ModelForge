#include <OCL/AttributeNavigationExpr.h>
#include <OCL/PrimaryExpr.h>
#include <algorithm>
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

void checkValidJavaModel(const MetaModel::MetaModel& metaModel){
    // Check valid inheritance and association ends
    for (const auto &metaClassPair : metaModel.getClasses()){
        if (metaClassPair.second->getSuperClasses().size() > 1){
            throw std::runtime_error("Can't generate to Java, class <" + metaClassPair.second->getName() + "> inherits from multiple classes, which is not allowed in Java");
        }
    }

    for (const auto &metaAssociationPair : metaModel.getAssociations()){
        if (metaAssociationPair.second->getAssociationEnds().size() > 2){
            throw std::runtime_error("Can't generate to Java, associtaion <" + metaAssociationPair.second->getName() + "> has more than 2 associaton ends. Not supported yet");
        }
    }

    for (const auto &metaAssocClassPair : metaModel.getAssociationClasses()){
        if (metaAssocClassPair.second->getSuperClasses().size() > 1){
            throw std::runtime_error("Can't generate to Java, association class <" + metaAssocClassPair.second->getName() + "> inherits from multiple association classes, which is not allowed in Java");
        }

        if (metaAssocClassPair.second->MetaAssociation::getAssociationEnds().size() > 2){
            throw std::runtime_error("Can't generate to Java, associtaion class <" + metaAssocClassPair.second->getName() + "> has more than 2 associaton ends. Not supported yet");
        }
    }
}

std::any VisitorJava::visit(const MetaModel::MetaModel& metaModel) {
    checkValidJavaModel(metaModel);

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

    for (const auto &metaEnumPair : metaModel.getEnums()) {
        metaEnumPair.second->accept(*this);
    }

    for (const auto &metaClassPair: metaModel.getClasses()) {
        metaClassPair.second->accept(*this);
    }

    for(const auto &metaAssociationPair : metaModel.getAssociations()){
        metaAssociationPair.second->accept(*this);
    }

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

    this->currentClassImports.clear();
    this->currentClassConstraints.clear();

    // TODO: add paramDeclaration of super class too
    auto superClasses = metaClass.getSuperClasses();
    if (!superClasses.empty()) {
        classString += " extends ";
        bool first = true;
        for (const auto &superClassPair : superClasses) {
            if (!first) classString += ", ";
            classString += superClassPair.second->getName();
            first = false;
        }
    }

    classString += "{\n\n";

    for(const auto &constraintPair : metaClass.getConstraints()){
        constraintPair.second->accept(*this);
    }

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

    if (this->currentClassConstraints.count("") > 0){
        classString += "\t// General constraints\n";
        for (auto attributeConstraint : this->currentClassConstraints.at("")){
            classString += "\t// " + attributeConstraint->toString() + "\n";
        }
        classString += "\n";
    }

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

    for (const auto& operationPair: metaClass.getOperations()){
        classString += std::any_cast<std::string>(operationPair.second->accept(*this));
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
    std::string filePath = this->directoryPath + "/" + metaAssociationClass.getName() + ".java";
    outFile.open(filePath);

    outFile << "package " << packageName << ";\n";

    std::string classString = "";

    classString += "public";

    if (metaAssociationClass.getIsAbstract()){
        classString += " abstract ";
    } else {
        classString += " ";
    }

    classString += "class " + metaAssociationClass.getName();

    this->currentClassImports.clear();
    this->currentClassConstraints.clear();

    // TODO: add paramDeclaration of super class too
    auto superClasses = metaAssociationClass.getSuperClasses();
    if (!superClasses.empty()) {
        classString += " extends ";
        bool first = true;
        for (const auto &superClassPair : superClasses) {
            if (!first) classString += ", ";
            classString += superClassPair.second->getName();
            first = false;
        }
    }

    classString += "{\n\n";

    for(const auto &constraintPair : metaAssociationClass.getConstraints()){
        constraintPair.second->accept(*this);
    }

    std::vector<JavaMemberCode> members;

    //attributes
    for(const auto &attributePair : metaAssociationClass.getAttributes()){
        members.push_back(std::any_cast<JavaMemberCode>(attributePair.second->accept(*this)));
    }

    //associations

    for(const auto &assocEndPair: metaAssociationClass.MetaAssociation::getAssociationEnds()){
        members.push_back(std::any_cast<JavaMemberCode>(assocEndPair.second->accept(*this)));
    }

    for(const auto &assocEndPair: metaAssociationClass.MetaClass::getAssociationEnds()){
        members.push_back(std::any_cast<JavaMemberCode>(assocEndPair.second->accept(*this)));
    }

    for (const auto& member : members) {
        classString += member.field;
    }
    classString += "\n";

    if (this->currentClassConstraints.count("") > 0){
        classString += "\t// General constraints\n";
        for (auto attributeConstraint : this->currentClassConstraints.at("")){
            classString += "\t//" + attributeConstraint->toString() + "\n";
        }
        classString += "\n";
    }

    classString += generateClassConstructor(metaAssociationClass, members);

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

    for (const auto& operationPair: metaAssociationClass.getOperations()){
        classString += std::any_cast<std::string>(operationPair.second->accept(*this));
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

std::string VisitorJava::generateAttributeConstraints(const MetaModel::MetaAttribute& metaAttribute) {
    std::string attributeConstraints = "";

    if (this->currentClassConstraints.count(metaAttribute.getName()) > 0){
        for (auto attributeConstraint : this->currentClassConstraints.at(metaAttribute.getName())){
            attributeConstraints += "//" + attributeConstraint->toString() + "\n";
        }
    }
    return attributeConstraints;
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
                    "\t\t" + generateAttributeConstraints(metaAttribute) +
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
    std::string operationString = "";

    std::string visibility = visibilityToString(metaOperation.getVisibility());
    std::string operationType = std::any_cast<std::string>(visitType(metaOperation.getReturnType()));

    std::string paramsDeclaration;
    for (const auto& variablePair : metaOperation.getVariables()) {
        if (!paramsDeclaration.empty()) paramsDeclaration += ", ";
        std::string paramType = std::any_cast<std::string>(visitType(variablePair.second->getType()));
        paramsDeclaration += paramType + " " + variablePair.second->getName();
    }

    operationString += "\t" + visibility + " " + operationType + " " + metaOperation.getName() + "(" + paramsDeclaration + "){\n";

    for (const auto& preConditionPair : metaOperation.getPreConditions()){
        operationString += "\t\t// Pre Condition <" + preConditionPair.second->getName() + ">: " +
                           preConditionPair.second->getExpression().toString() + "\n";
    }

    operationString += "\t\t/*\n\t" + metaOperation.getOperationDefinition() + "\n\t\t*/\n";

    for (const auto& postConditionPair : metaOperation.getPostConditions()){
        operationString += "\t\t// Post Condition <" + postConditionPair.second->getName() + ">: " +
                           postConditionPair.second->getExpression().toString() + "\n";
    }

    operationString += "\t}\n";

    return operationString;
}


std::any VisitorJava::visit(const MetaModel::MetaConstraint& metaConstraint) {
    const std::shared_ptr<MetaModel::Expr>& expr = metaConstraint.getExpressionPtr();
    if(expr->isComplexExpr()){
        this->currentClassConstraints[""].push_back(expr);
        return 0;
    }
    auto attrName = findSingleAttribute(expr);
    this->currentClassConstraints[attrName].push_back(expr);

    return 0;
}

std::string VisitorJava::findSingleAttribute(const std::shared_ptr<MetaModel::Expr>& expr) {
    // Case 1: direct attribute navigation
    if (auto attrNavExpr = std::dynamic_pointer_cast<MetaModel::AttributeNavigationExpr>(expr)) {
        return attrNavExpr->getAttribute().getName();
    }

    // Case 2: composite expression -> collect names recursively
    std::string result = "";
    for (const auto& child : expr->getChildren()) {

        std::string childName = findSingleAttribute(child);

        if (result.empty()) {
            result = childName;
        } else if (childName != "" && result != childName) {
            // two different attributes -> not single-attribute
            return "";
        }
    }
    return result;
}

std::any VisitorJava::visit(const MetaModel::MetaAssociationEnd& metaAssociationEnd) {
    JavaMemberCode member;

    if (!metaAssociationEnd.getIsNavigable()) return member;

    member.name = metaAssociationEnd.getRole();
    std::string capitalizedName = capitalize(member.name);
    std::string visibility = visibilityToString(metaAssociationEnd.getVisibility());

    std::string targetType = metaAssociationEnd.getClass().getName();

    bool assocIsAssocClass = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(
                                metaAssociationEnd.getAssociationSharedPtr()) != nullptr;
    bool endClassIsAssocClass = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(
                                    metaAssociationEnd.getClassSharedPtr()) != nullptr;

    const MetaModel::MetaMultiplicity& multiplicity = metaAssociationEnd.getMultiplicity();
    int lowerBound = multiplicity.getRanges().empty() ? 1 : multiplicity.getRanges().front()->getLowerBound();
    int upperBound = multiplicity.getRanges().empty() ? 1 : multiplicity.getRanges().front()->getUpperBound();

    bool isMultiple = (upperBound == -1 || upperBound > 1);

    bool otherEndIsMultiple = false;
    if(assocIsAssocClass && !endClassIsAssocClass){
        for(const auto& assocEnd : metaAssociationEnd.getAssociation().getAssociationEnds()){
            if(assocEnd.first != metaAssociationEnd.getRole()){
                const MetaModel::MetaMultiplicity& otherEndMultiplicity = assocEnd.second->getMultiplicity();
                int otherEndLowerBound = otherEndMultiplicity .getRanges().empty() ? 1 : otherEndMultiplicity .getRanges().front()->getLowerBound();
                int otherEndUpperBound = otherEndMultiplicity .getRanges().empty() ? 1 : otherEndMultiplicity .getRanges().front()->getUpperBound();
                otherEndIsMultiple = (otherEndUpperBound == -1 || otherEndLowerBound > 1);
                break;
            }
        }
    }

    std::string collectionType = "List<" + targetType + ">";
    std::string implementationType = "ArrayList<" + targetType + ">";

    if (isMultiple) {
        currentClassImports.insert("java.util.List");
        currentClassImports.insert("java.util.ArrayList");
        currentClassImports.insert("java.util.Collections");

        member.type = collectionType;
        member.field = "\tprivate " + collectionType + " " + member.name + ";\n";

        std::string singularName = (member.name.back() == 's') ? member.name.substr(0, member.name.size() - 1) : member.name;

        member.getter = "";
        member.getter = "\t" + visibility + " " + collectionType + " get" + capitalizedName + "() {\n" +
                        "\t\treturn Collections.unmodifiableList(this." + member.name + ");\n" +
                        "\t}\n\n";

        if (lowerBound > 1) { //n..m && n..*
            if(assocIsAssocClass && endClassIsAssocClass){
                member.paramDeclaration = "";
                member.paramSet = member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "(" + (upperBound==-1 ? "" : "" + std::to_string(upperBound) + "" ) + ");\n";
            } else {
                for (int i = 1; i <= lowerBound; ++i) {
                    if (i > 1) member.paramDeclaration += ", ";
                    member.paramDeclaration += targetType + " " + singularName;
                    if (i > 1) member.paramDeclaration += std::to_string(i);
                }

                member.paramSet = member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "(" + (upperBound==-1 ? "" : "" + std::to_string(upperBound) + "" ) + ");\n";
                for (int i = 1; i <= lowerBound; ++i) {
                    std::string paramName = member.name + (i > 1 ? std::to_string(i) : "");
                    member.paramSet += "\t\t\tthis.add" + capitalize(singularName) + "(" +paramName + ");\n";
                }
            }

            member.adder = "\t" + visibility + " void add" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                           (upperBound > 1
                                ? "\t\tif (this." + member.name + ".size() >= " + std::to_string(upperBound) + ") {\n" +
                                      "\t\t\tthrow new IllegalStateException(\"Cannot add element: maximum multiplicity of " +
                                      std::to_string(upperBound) + " would be violated.\");\n" +
                                      "\t\t}\n"
                                : "") +
                           "\t\tthis." + member.name + ".add(element);\n" +
                           ((assocIsAssocClass && !endClassIsAssocClass)
                                ? "\t\telement." +
                                      ((otherEndIsMultiple)
                                           ? "add" + capitalize(metaAssociationEnd.getAssociation().getName())
                                           : "set" + capitalize(metaAssociationEnd.getAssociation().getName())) + "(this);\n"
                                : "") +
                           "\t}\n\n";

            member.remover = "\t" + visibility + " void remove" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                             "\t\tif (this." + member.name + ".size() <= " + std::to_string(lowerBound) + ") {\n" +
                             "\t\t\tthrow new IllegalStateException(\"Cannot remove element: minimum multiplicity of " +
                             std::to_string(lowerBound) + " would be violated.\");\n" +
                             "\t\t}\n" +
                             "\t\tthis." + member.name + ".remove(element);\n" +
                             ((assocIsAssocClass && !endClassIsAssocClass)
                                  ? "\t\telement." +
                                        ((otherEndIsMultiple)
                                             ? "remove" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(this);\n"
                                             : "set" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(null)") + ";\n"
                                  : "") +
                             "\t}\n\n";


        } else if (lowerBound == 1) { //1..m && 1..*
            std::string paramName = singularName;
            if(assocIsAssocClass && endClassIsAssocClass){
                member.paramDeclaration = "";
                member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "(" + (upperBound==-1 ? "" : "" + std::to_string(upperBound) + "" ) + ");\n";
            } else {
                member.paramDeclaration = targetType + " " + paramName;
                member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "(" + (upperBound==-1 ? "" : "" + std::to_string(upperBound) + "" ) + ");\n" +
                                  "\t\tthis." + member.name + ".add(" + paramName + ");\n";
            }

            member.adder = "\t" + visibility + " void add" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                           (upperBound > 1
                                ? "\t\tif (this." + member.name + ".size() >= " + std::to_string(upperBound) + ") {\n" +
                                      "\t\t\tthrow new IllegalStateException(\"Cannot add element: maximum multiplicity of " +
                                      std::to_string(upperBound) + " would be violated.\");\n" +
                                      "\t\t}\n"
                                : "") +
                           "\t\tthis." + member.name + ".add(element);\n" +
                           ((assocIsAssocClass && !endClassIsAssocClass)
                                ? "\t\telement." +
                                      ((otherEndIsMultiple)
                                           ? "add" + capitalize(metaAssociationEnd.getAssociation().getName())
                                           : "set" + capitalize(metaAssociationEnd.getAssociation().getName())) + "(this);\n"
                                : "") +
                           "\t}\n\n";

            member.remover = "\t" + visibility + " void remove" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                             "\t\tif (this." + member.name + ".size() <= " + std::to_string(lowerBound) + ") {\n" +
                             "\t\t\tthrow new IllegalStateException(\"Cannot remove element: minimum multiplicity of " +
                             std::to_string(lowerBound) + " would be violated.\");\n" +
                             "\t\t}\n" +
                             "\t\tthis." + member.name + ".remove(element);\n" +
                             ((assocIsAssocClass && !endClassIsAssocClass)
                                  ? "\t\telement." +
                                        ((otherEndIsMultiple)
                                             ? "remove" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(this);\n"
                                             : "set" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(null)") + ";\n"
                                  : "") +
                             "\t}\n\n";

        } else if (lowerBound <= 0) { // 0..m && 0..*
            member.paramDeclaration = "";
            member.paramSet = "\t\tthis." + member.name + " = new " + implementationType + "();\n";

            member.adder = "\t" + visibility + " void add" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                           "\t\tthis." + member.name + ".add(element);\n" +
                           ((assocIsAssocClass && !endClassIsAssocClass)
                                ? "\t\telement." +
                                      ((otherEndIsMultiple)
                                           ? "add" + capitalize(metaAssociationEnd.getAssociation().getName())
                                           : "set" + capitalize(metaAssociationEnd.getAssociation().getName())) + "(this);\n"
                                : "") +
                           "\t}\n\n";

            member.remover = "\t" + visibility + " void remove" + capitalize(singularName) + "(" + targetType + " element) {\n" +
                             "\t\tthis." + member.name + ".remove(element);\n" +
                             ((assocIsAssocClass && !endClassIsAssocClass)
                                  ? "\t\telement." +
                                        ((otherEndIsMultiple)
                                             ? "remove" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(this);\n"
                                             : "set" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(null)") + ";\n"
                                  : "") +
                             "\t}\n\n";
        }

    } else {
        member.type = targetType;
        member.field = "\tprivate " + targetType + " " + member.name + ";\n";

        if(assocIsAssocClass && endClassIsAssocClass){
            member.paramDeclaration = "";
            member.paramSet = "";
        } else{
            member.paramDeclaration = targetType + " " + member.name;
            member.paramSet = "\t\tthis.set" + capitalizedName + "(" + member.name + ");\n";
        }

        member.getter = "\t" + visibility + " " + targetType + " get" + capitalizedName + "() {\n" +
                        "\t\treturn this." + member.name + ";\n" +
                        "\t}\n\n";

        member.setter = "\t" + visibility + " void set" + capitalizedName + "(" + targetType + " " + member.name + ") {\n" +
                        ((lowerBound == 1)
                             ? "\t\tif (" + member.name + " == null) {\n" +
                                   "\t\t\tthrow new IllegalArgumentException(\"" + member.name + " must not be null.\");\n\t\t}\n"
                             : ""
                         ) +
                        ((assocIsAssocClass && !endClassIsAssocClass)
                           ? "\t\tif (this." + member.name + " != null) {\n" +
                                  "\t\t\tthis." + member.name + "." +
                                       ((otherEndIsMultiple)
                                            ? "remove" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(this);\n"
                                            : "set" + capitalize(metaAssociationEnd.getAssociation().getName()) + "(null);\n") +
                             "\t\t}\n"
                            : "") +

                        "\t\tthis." + member.name + " = " + member.name + ";\n" +
                        ((assocIsAssocClass && !endClassIsAssocClass)
                             ? "\t\t" + member.name + "." +
                                   ((otherEndIsMultiple)
                                        ? "add" + capitalize(metaAssociationEnd.getAssociation().getName())
                                        : "set" + capitalize(metaAssociationEnd.getAssociation().getName())) + "(this);\n"
                             : "") +
                        "\t}\n\n";
    }

    return member;
}


}
