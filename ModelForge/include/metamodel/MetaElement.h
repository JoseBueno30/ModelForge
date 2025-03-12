#ifndef METAELEMENT_H
#define METAELEMENT_H

namespace ModelToText {
class VisitorInterface;  // Forward declaration
}

namespace MetaModel{

class MetaElement{

public:
    virtual void accept(ModelToText::VisitorInterface& visitor) const = 0;
};

}

#endif // METAELEMENT_H
