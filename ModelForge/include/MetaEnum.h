#ifndef METAENUM_H
#define METAENUM_H

#include "MetaType.h"

#include<string>


namespace MetaModel {

class MetaEnumElement{
private:
    std::string name;
};

class MetaEnum : SimpleType{
private:
    std::string name;
};

}

#endif // METAENUM_H
