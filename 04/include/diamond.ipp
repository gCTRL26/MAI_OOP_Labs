#pragma once

#include "diamond.hpp"
#include "exception.hpp"

namespace figure {

template<Arithmetic T>
bool Diamond<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const {
    Point<T> points_arr[DIAMONDANGLES] = {p1, p2, p3, p4};
    for (size_t i = 0; i != DIAMONDANGLES; ++i) {
        for (size_t j = i + 1; j != DIAMONDANGLES; ++j) {
            if (points_arr[i] == points_arr[j]) {
                return false;
            }
        }
    }
    double side1 = Distance(p1, p2);
    double side2 = Distance(p2, p3);
    double side3 = Distance(p3, p4);
    double side4 = Distance(p4, p1);

    double d1 = Distance(p1, p3);
    double d2 = Distance(p2, p4);
    double temp_area = (d1 * d2) / 2.0;
    return (std::fabs(side1 - side2) < EPS && std::fabs(side2 - side3) < EPS && std::fabs(side3 - side4) < EPS && temp_area > EPS);
}

template<Arithmetic T>
Diamond<T>::Diamond() {
    points_ = std::make_unique<Point<T>[]>(DIAMONDANGLES);
    points_[0] = Point<T>(0, 1);
    points_[1] = Point<T>(1, 0);
    points_[2] = Point<T>(0, -1);
    points_[3] = Point<T>(-1, 0);
}

template<Arithmetic T>
Diamond<T>::Diamond(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    if (!Validate(p1, p2, p3, p4)) {
        throw exceptions::InvalidPointsException("Diamond: wrong points");
    }
    points_ = std::make_unique<Point<T>[]>(DIAMONDANGLES);
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
    points_[3] = p4;
}

template<Arithmetic T>
Diamond<T>::Diamond(const Diamond<T>& other) {
    points_ = std::make_unique<Point<T>[]>(DIAMONDANGLES);
    for (size_t i = 0; i != DIAMONDANGLES; ++i) {
        points_[i] = other.points_[i];
    }
}

template<Arithmetic T>
Diamond<T>& Diamond<T>::operator=(const Diamond<T>& other) {
    if (this == &other) {
        return *this;
    }
    Diamond<T> tmp = other;
    std::swap(tmp.points_, points_);
    return *this;
}

template<Arithmetic T>
Point<T> Diamond<T>::Center() const {
    return Point<T>((points_[0].x + points_[2].x) / 2.0, (points_[0].y + points_[2].y) / 2.0);
}

template<Arithmetic T>
double Diamond<T>::Area() const {
    double d1 = Distance(points_[0], points_[2]);
    double d2 = Distance(points_[1], points_[3]);
    return (d1 * d2) / 2.0;    
}

template<Arithmetic T>
Diamond<T>::operator double() const {
    return Area();

}

template<Arithmetic T>
bool operator==(const Diamond<T>& d1, const Diamond<T>& d2) {
    double d1_side = Distance(d1.points_[0], d1.points_[1]);
    double d2_side = Distance(d2.points_[0], d2.points_[1]);
    return (std::fabs(d1_side - d2_side) < EPS && std::fabs(d1.Area() - d2.Area()) < EPS);
}

template<Arithmetic T>
bool operator!=(const Diamond<T>& d1, const Diamond<T>& d2) {
    return !(d1 == d2);
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Diamond<T>& d) {
    os << "[";
    for (size_t i = 0; i != DIAMONDANGLES; ++i) {
        os << d.points_[i];
    }
    os << "]" << std::endl;
    return os;
}
template<Arithmetic T>
std::istream& operator>>(std::istream& is, Diamond<T>& d) {
    Point<T> input_points[DIAMONDANGLES];
    for (size_t i = 0; i != DIAMONDANGLES; ++i) {
        is >> input_points[i];
    }
    try {
        Diamond tmp(input_points[0], input_points[1], input_points[2], input_points[3]);
        std::swap(d.points_, tmp.points_);
    } catch (exceptions::InvalidPointsException& e) {
        std::cerr << "Diamond: wrong points from input" << std::endl;
        return is;
    }
    return is;
}
}