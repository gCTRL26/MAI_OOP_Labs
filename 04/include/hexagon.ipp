#pragma once

#include "hexagon.hpp"
#include "exception.hpp"
#include <cmath>

namespace figure {

template<Arithmetic T>
bool Hexagon<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5, const Point<T>& p6) const {
    Point<T> points_arr[HEXAGONANGLES] = {p1, p2, p3, p4, p5, p6};
    for (size_t i = 0; i != HEXAGONANGLES; ++i) {
        for (size_t j = i + 1; j != HEXAGONANGLES; ++j) {
            if (points_arr[i] == points_arr[j]) {
                return false;
            }
        }
    }
    double side1 = Distance(p1, p2);
    double side2 = Distance(p2, p3);
    double side3 = Distance(p3, p4);
    double side4 = Distance(p4, p5);
    double side5 = Distance(p5, p6);
    double side6 = Distance(p6, p1);

    
    bool is_ok = (std::fabs(side1 - side2) < EPS && 
            std::fabs(side2 - side3) < EPS && 
            std::fabs(side3 - side4) < EPS && 
            std::fabs(side4 - side5) < EPS && 
            std::fabs(side5 - side6) < EPS);
    if (!is_ok) {
        return false;
    }
    double temp_area = (pow(side1, 2) * 3 * sqrt(3)) / 2;
    return temp_area > EPS;
}

template<Arithmetic T>
Hexagon<T>::Hexagon() {
    points_ = std::make_unique<Point<T>[]>(HEXAGONANGLES);
    points_[0] = Point<T>(1, 0);
    points_[1] = Point<T>(0.5, 0.86603);
    points_[2] = Point<T>(-0.5, 0.86603);
    points_[3] = Point<T>(-1, 0);
    points_[4] = Point<T>(-0.5, -0.86603);
    points_[5] = Point<T>(0.5, -0.86603);
}

template<Arithmetic T>
Hexagon<T>::Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5, const Point<T>& p6) {
    if (!Validate(p1, p2, p3, p4, p5, p6)) {
        throw exceptions::InvalidPointsException("Hexagon: wrong points");
    }
    points_ = std::make_unique<Point<T>[]>(HEXAGONANGLES);
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
    points_[3] = p4;
    points_[4] = p5;
    points_[5] = p6;
}

template<Arithmetic T>
Hexagon<T>::Hexagon(const Hexagon<T>& other) {
    points_ = std::make_unique<Point<T>[]>(HEXAGONANGLES);
    for (size_t i = 0; i != HEXAGONANGLES; ++i) {
        points_[i] = other.points_[i];
    }
}

template<Arithmetic T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon<T>& other) {
    if (this == &other) {
        return *this;
    }
    Hexagon<T> tmp = other;
    std::swap(tmp.points_, points_);
    return *this;
}

template<Arithmetic T>
Point<T> Hexagon<T>::Center() const {
    T xc = 0;
    T yc = 0;
    for (size_t i = 0; i != HEXAGONANGLES; ++i) {
        xc += points_[i].x;
        yc += points_[i].y;
    }
    return Point<T>(xc / HEXAGONANGLES, yc / HEXAGONANGLES);
}

template<Arithmetic T>
double Hexagon<T>::Area() const {
    double h1 = Distance(points_[0], points_[1]);
    return (pow(h1, 2) * 3 * sqrt(3)) / 2;    
}

template<Arithmetic T>
Hexagon<T>::operator double() const {
    return Area();

}

template<Arithmetic T>
bool operator==(const Hexagon<T>& h1, const Hexagon<T>& h2) {
    double h1_side = Distance(h1.points_[0], h1.points_[1]);
    double h2_side = Distance(h2.points_[0], h2.points_[1]);
    return (std::fabs(h1_side - h2_side) < EPS && std::fabs(h1.Area() - h2.Area()) < EPS);
}

template<Arithmetic T>
bool operator!=(const Hexagon<T>& h1, const Hexagon<T>& h2) {
    return !(h1 == h2);
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Hexagon<T>& h) {
    os << "[";
    for (size_t i = 0; i != HEXAGONANGLES; ++i) {
        os << h.points_[i];
    }
    os << "]" << std::endl;
    return os;
}
template<Arithmetic T>
std::istream& operator>>(std::istream& is, Hexagon<T>& h) {
    Point<T> input_points[HEXAGONANGLES];
    for (size_t i = 0; i != HEXAGONANGLES; ++i) {
        is >> input_points[i];
    }
    try {
        Hexagon tmp(input_points[0], input_points[1], input_points[2], input_points[3], input_points[4], input_points[5]);
        std::swap(h.points_, tmp.points_);
    } catch (exceptions::InvalidPointsException& e) {
        std::cerr << "Hexagon: wrong points from input" << std::endl;
        return is;
    }
    return is;
}
}