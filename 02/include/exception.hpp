#pragma once

#include <stdexcept>
#include <string>

// my own exceptions

namespace exception {
    class NaNException: public std::runtime_error {
    public:
        explicit NaNException(const std::string& text): std::runtime_error(text) {}
    };

    class NegativeException: public std::runtime_error {
    public:
        explicit NegativeException(const std::string& text): std::runtime_error(text) {}
    };
}
