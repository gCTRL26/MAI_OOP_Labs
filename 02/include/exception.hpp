#pragma once

#include <exception>
#include <string>

namespace exception {
    class NaNException: std::exception {
    public:
        explicit NaNException(const std::string& text):
            error_message_(text){}

        const char* what() const noexcept override {
            return error_message_.data();
        }

    private:
        std::string_view error_message_;
    };

    class NegativeException: std::exception {
    public:
        explicit NegativeException(const std::string& text):
            error_message_(text){}

        const char* what() const noexcept override {
            return error_message_.data();
        }

    private:
        std::string_view error_message_;
    };
}
