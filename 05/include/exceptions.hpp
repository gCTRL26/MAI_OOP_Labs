#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
class VectorOutOfRange: public std::out_of_range {
public:
    explicit VectorOutOfRange(const std::string& text): std::out_of_range(text) {}
};
}