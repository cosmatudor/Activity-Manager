#include "Exceptions.h"

#include <utility>

ostream &operator<<(ostream &out, const RepositoryExcepetion &exception) {
    out << exception.message;
    return out;
}

const string &ValidationException::getMessage() const {
    return message;
}

const string &UIException::getMessage() const {
    return message;
}
