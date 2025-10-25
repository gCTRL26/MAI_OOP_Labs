#include "../include/figure.hpp"
#include <cmath>

namespace figure {
    Point::Point(double x, double y) : x(x), y(y) {}

    bool operator==(const Point& p1, const Point& p2) {
        bool x = std::fabs(p1.x - p2.x) < EPS;
        bool y = std::fabs(p1.y - p2.y) < EPS;
        return (x && y);
    }
    bool operator!=(const Point& p1, const Point& p2) {
        return !(p1 == p2);
    }

    double Distance(const Point& p1, const Point& p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }

    std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }  
}