#ifndef VISIBILITY_H
#define VISIBILITY_H

#include <string>

namespace MetaModel {

enum class Visibility {
    Public,
    Private,
    Protected,
    Package
};

}

std::string fromVisibilityToStdString(MetaModel::Visibility vis);

#endif // VISIBILITY_H
