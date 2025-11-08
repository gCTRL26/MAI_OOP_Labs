#pragma once

#include "figure.hpp"

namespace figure {

template<Arithmetic T>
bool operator==(const Point<T>& p1, const Point<T>& p2) {
    bool x = std::fabs(p1.x - p2.x) < EPS;
    bool y = std::fabs(p1.y - p2.y) < EPS;
    return (x && y);   
}

template<Arithmetic T>
bool operator!=(const Point<T>& p1, const Point<T>& p2) {
    return !(p1 == p2);
}

template<Arithmetic T>
double Distance(const Point<T>& p1, const Point<T>& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template<Arithmetic T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}
}