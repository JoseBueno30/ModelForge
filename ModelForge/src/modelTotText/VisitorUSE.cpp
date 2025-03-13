#include <modelToText/VisitorUSE.h>
#include <stdexcept>

namespace ModelToText {

VisitorUSE::VisitorUSE(const std::string& filename) {
    outFile.open(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }
}

VisitorUSE::~VisitorUSE() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void VisitorUSE::visit(MetaModel::MetaModel metaModel){
    outFile << "model " << metaModel.getName() <<"\n\n";

    for(const auto &metaEnumPair : metaModel.getEnums()){
        metaEnumPair.second->accept(*this);
    }

    for(const auto &metaClassPair : metaModel.getClasses()){
        metaClassPair.second->accept(*this);
    }
}

void VisitorUSE::visit(MetaModel::MetaEnum metaEnum){
    outFile << "enum " << metaEnum.getName() << " {";

    auto metaEnumElements = metaEnum.getElements();
    auto elementsIterator = metaEnumElements.begin();

    outFile << elementsIterator->second->getName();

    elementsIterator++;

    for(; elementsIterator != metaEnumElements.end(); elementsIterator++){
        outFile << ", " << elementsIterator->second->getName();
    }

    outFile <<"}" << "\n\n";

}

void VisitorUSE::visit(MetaModel::MetaClass metaClass){
    //If class has already been visited, do nothing
    if(visitedClasses.find(metaClass.getName()) != visitedClasses.end()){
        return;
    }

    outFile << "class " << metaClass.getName();

    //Generalization
    auto superClasses = metaClass.getSuperClasses();

    if(superClasses.size() > 0){
        outFile << " < ";

        auto superClassesIterator = superClasses.begin();
        auto& superClass = superClassesIterator->second;

        if(visitedClasses.find(superClass->getName()) == visitedClasses.end()){
            superClass->accept(*this);
        }

        outFile << superClass->getName();

        for(; superClassesIterator != superClasses.end(); superClassesIterator++){
            superClass = superClassesIterator->second;
            if(visitedClasses.find(superClass->getName()) == visitedClasses.end()){
                superClass->accept(*this);
            }

            outFile << ", " << superClass->getName();
        }

        outFile << "\n";
    }


    //Attributes
    auto attributes = metaClass.getAttributes();

    if(attributes.size() > 0){
        outFile << "attributes" << "\n";

        for(const auto &attributePair : attributes){
            outFile << attributePair.second->toString() << "\n";
        }
    }

    //Operations
    auto operations = metaClass.getOperations();

    if(operations.size() > 0){
        outFile << "operations" << "\n";

        for(const auto &operationPair : operations){

        }
    }

    //Constraints

    //StateMachines


    outFile << "end" << "\n\n";
}

void VisitorUSE::visit(MetaModel::MetaAssociation metaAssociation){

}

void VisitorUSE::visit(MetaModel::MetaAssociationClass metaAssociationClass){

}

void VisitorUSE::save() {
    if (outFile.is_open()) {
        outFile.flush();
    }
}

}
