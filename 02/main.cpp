#include <iostream>
#include <ostream>
#include <string>
#include "decimal.hpp"
#include "exception.hpp"
#include "include/decimal.hpp"
#include "include/exception.hpp"

int main() {
    std::cout << "Enter number to see it" << std::endl;
    std::string input;
    std::cin >> input;
    try {
        decimal::Decimal number(input);
        std::cout << number.ShowNumber() << std::endl;
    } catch (exception::NaNException) {
        std::cout << "Not a number" << std::endl;
    }
    return 0;
}