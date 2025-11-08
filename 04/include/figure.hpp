#pragma once

#include "concept.hpp"

#include <cmath>
#include <iostream>

namespace figure {
constexpr const double EPS = 1e-6;
constexpr const int DIAMONDANGLES = 4;
constexpr const int PENTAGONANGLES = 5;
constexpr const int HEXAGONANGLES = 6;

template<Arithmetic T>
class Point {
  public:
    T x = 0.0;
    T y = 0.0;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
};
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

template<Arithmetic T>
class Figure {
  public:
    virtual Point<T> Center() const = 0;
    virtual operator double() const = 0;
    virtual double Area() const = 0;
    virtual ~Figure() = default;
};
}