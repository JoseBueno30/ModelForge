#include <filesystem>
#include <modelToText/VisitorJava.h>



namespace ModelToText {

VisitorJava::VisitorJava(const std::string& directoryPath) {
    this->directoryPath = directoryPath + "/java";

    std::filesystem::path javaDir(this->directoryPath);

    std::error_code ec;
    if (!std::filesystem::exists(javaDir)) {
        if (!std::filesystem::create_directories(javaDir, ec)) {
            throw std::runtime_error("Failed to create directory: " + javaDir.string() + ", error: " + ec.message());
        }
    }
}

VisitorJava::~VisitorJava() {}

std::any VisitorJava::visit(MetaModel::MetaModel metaModel) {
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

std::any VisitorJava::visit(MetaModel::MetaEnum metaEnum) {
    std::string filePath = this->directoryPath + "/" + metaEnum.getName() + ".java";
    std::ofstream file(filePath);

    file << "public enum " << metaEnum.getName() << " {\n";
    for(const auto &metaEnumPair: metaEnum.getElements()){
        file << "\t" << metaEnumPair.second->getName() << ",\n";
    }
    file << "}\n";
    file.close();

    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaClass metaClass) {
    return 0;
}

std::any VisitorJava::visit(MetaModel::MetaAssociation metaAssociation) {
    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaAssociationClass metaAssociationClass) {
    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaAttribute metaAttribute) {
    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaOperation metaOperation) {
    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaConstraint metaConstraint) {
    return 0;
}


std::any VisitorJava::visit(MetaModel::MetaAssociationEnd metaAssociatonEnd) {
    return 0;
}


}
