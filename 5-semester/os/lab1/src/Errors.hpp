#pragma once

#include <stdexcept>


namespace lab {

    /**
     * @class CantCreateFIFOException
     * @brief Exception thrown if named pipe creation failed
     */
    class CantCreateFIFOException : public std::runtime_error {
    public:
        explicit CantCreateFIFOException(const std::string& what)
            : std::runtime_error(what) {}
    };

} // namespace lab