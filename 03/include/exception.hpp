#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
class InvalidPointsException: std::runtime_error {
public:
    explicit InvalidPointsException(const std::string& text): std::runtime_error(text) {}
};
class VectorOutOfRange: std::out_of_range {
public:
    explicit VectorOutOfRange(const std::string& text): std::out_of_range(text) {}
};
}