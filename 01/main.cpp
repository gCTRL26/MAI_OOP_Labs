#include <iostream>
#include <string>

#include "filter.hpp"

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::string result = filter::Filter(input);
    std::cout << result << std::endl;
    return 0;
}