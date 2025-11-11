#pragma once

#include "pentagon.hpp"
#include "exception.hpp"

namespace figure {

template<Arithmetic T>
bool Pentagon<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5) const {
    Point<T> points_arr[PENTAGONANGLES] = {p1, p2, p3, p4, p5};
    for (size_t i = 0; i != PENTAGONANGLES; ++i) {
        for (size_t j = i + 1; j != PENTAGONANGLES; ++j) {
            if (points_arr[i] == points_arr[j]) {
                return false;
            }
        }
    }
    double side1 = Distance(p1, p2);
    double side2 = Distance(p2, p3);
    double side3 = Distance(p3, p4);
    double side4 = Distance(p4, p5);
    double side5 = Distance(p5, p1);

    double temp_area = (sqrt(5) * sqrt(5 + 2 * sqrt(5))) / 4 * pow(side1, 2);
    return (std::fabs(side1 - side2) < EPS && 
            std::fabs(side2 - side3) < EPS && 
            std::fabs(side3 - side4) < EPS && 
            std::fabs(side4 - side5) < EPS && 
            temp_area > EPS);
}

template<Arithmetic T>
Pentagon<T>::Pentagon() {
    points_ = std::make_unique<Point<T>[]>(PENTAGONANGLES);
    points_[0] = Point<T>(0, 1);
    points_[1] = Point<T>(0.95106, 0.30902);
    points_[2] = Point<T>(0.58779, -0.80902);
    points_[3] = Point<T>(-0.58779, -0.80902);
    points_[4] = Point<T>(-0.95106, 0.30902);
}

template<Arithmetic T>
Pentagon<T>::Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5) {
    if (!Validate(p1, p2, p3, p4, p5)) {
        throw exceptions::InvalidPointsException("Pentagon: wrong points");
    }
    points_ = std::make_unique<Point<T>[]>(PENTAGONANGLES);
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
    points_[3] = p4;
    points_[4] = p5;
}

template<Arithmetic T>
Pentagon<T>::Pentagon(const Pentagon<T>& other) {
    points_ = std::make_unique<Point<T>[]>(PENTAGONANGLES);
    for (size_t i = 0; i != PENTAGONANGLES; ++i) {
        points_[i] = other.points_[i];
    }
}

template<Arithmetic T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other) {
    if (this == &other) {
        return *this;
    }
    Pentagon<T> tmp = other;
    std::swap(tmp.points_, points_);
    return *this;
}

template<Arithmetic T>
Point<T> Pentagon<T>::Center() const {
    T xc = 0;
    T yc = 0;
    for (size_t i = 0; i != PENTAGONANGLES; ++i) {
        xc += points_[i].x;
        yc += points_[i].y;
    }
    return Point<T>(xc / PENTAGONANGLES, yc / PENTAGONANGLES);
}

template<Arithmetic T>
double Pentagon<T>::Area() const {
    double p1 = Distance(points_[0], points_[1]);
    return (sqrt(5) * sqrt(5 + 2 * sqrt(5))) / 4 * pow(p1, 2); 
}

template<Arithmetic T>
Pentagon<T>::operator double() const {
    return Area();

}

template<Arithmetic T>
bool operator==(const Pentagon<T>& h1, const Pentagon<T>& h2) {
    double h1_side = Distance(h1.points_[0], h1.points_[1]);
    double h2_side = Distance(h2.points_[0], h2.points_[1]);
    return (std::fabs(h1_side - h2_side) < EPS && std::fabs(h1.Area() - h2.Area()) < EPS);
}

template<Arithmetic T>
bool operator!=(const Pentagon<T>& h1, const Pentagon<T>& h2) {
    return !(h1 == h2);
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Pentagon<T>& p) {
    os << "[";
    for (size_t i = 0; i != PENTAGONANGLES; ++i) {
        os << p.points_[i];
    }
    os << "]" << std::endl;
    return os;
}
template<Arithmetic T>
std::istream& operator>>(std::istream& is, Pentagon<T>& h) {
    Point<T> input_points[PENTAGONANGLES];
    for (size_t i = 0; i != PENTAGONANGLES; ++i) {
        is >> input_points[i];
    }
    try {
        Pentagon tmp(input_points[0], input_points[1], input_points[2], input_points[3], input_points[4]);
        std::swap(h.points_, tmp.points_);
    } catch (exceptions::InvalidPointsException& e) {
        std::cerr << "Pentagon: wrong points from input" << std::endl;
        return is;
    }
    return is;
}
}