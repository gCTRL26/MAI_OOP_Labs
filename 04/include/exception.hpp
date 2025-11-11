#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
class InvalidPointsException: public std::runtime_error {
public:
    explicit InvalidPointsException(const std::string& text): std::runtime_error(text) {}
};
class VectorOutOfRange: public std::out_of_range {
public:
    explicit VectorOutOfRange(const std::string& text): std::out_of_range(text) {}
};
}