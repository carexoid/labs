#pragma once

#include <stdexcept>


namespace lab {

class CantCreateFIFOException : public std::runtime_error {
public:
    CantCreateFIFOException(const std::string& what)
        : std::runtime_error(what) {}
};

} // namespace lab