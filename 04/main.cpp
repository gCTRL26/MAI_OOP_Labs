#include "diamond.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

int main() {
    figure::Diamond<double> s;
    std::cout << "Enter the diamond points:" << std::endl;
    std::cin >> s;

    figure::Pentagon<double> r;
    std::cout << "Enter the pentagon points:" << std::endl;
    std::cin >> r;

    figure::Hexagon<double> t;
    std::cout << "Enter the hexagon points:" << std::endl;
    std::cin >> t;

    std::cout << "Square: " << s << std::endl;
    std::cout << "Rectangle: " << r << std::endl;
    std::cout << "Trapezoid: " << t << std::endl;
    return 0;
}