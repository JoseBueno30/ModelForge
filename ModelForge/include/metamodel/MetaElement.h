#ifndef METAELEMENT_H
#define METAELEMENT_H

#include <any>


namespace ModelToText {
class VisitorInterface;  // Forward declaration
}

namespace MetaModel{

class MetaElement{

public:
    virtual std::any accept(ModelToText::VisitorInterface& visitor) const = 0;
};

}

#endif // METAELEMENT_H
