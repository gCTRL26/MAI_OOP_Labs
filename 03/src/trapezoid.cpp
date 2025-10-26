#include "trapezoid.hpp"
#include "exception.hpp"
#include "figure.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>

namespace figure {
Trapezoid::Trapezoid(): Trapezoid(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)) {}
Trapezoid::Trapezoid(Point p1, Point p2, Point p3, Point p4) {
    if (!Validate(p1, p2, p3, p4)) {
        throw exceptions::InvalidPointsException("Trapezoid: Wrong points");
    }
    points_ = new Point[TRAPEZOIDANGLES] {p1, p2, p3, p4};
}
Trapezoid::Trapezoid(const Trapezoid& other) {
    points_ = new Point[TRAPEZOIDANGLES];
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        points_[i] = other.points_[i];
    }
}
Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this == &other) {
        return *this;
    }
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        points_[i] = other.points_[i];
    }
    return *this;
}
Point Trapezoid::Center() const {
    double mid_x = (points_[0].x + points_[1].x + points_[2].x + points_[3].x) / 4;
    double mid_y = (points_[0].y + points_[1].y + points_[2].y + points_[3].y) / 4;
    return Point(mid_x, mid_y);
}
double Trapezoid::Area() const {
    double base1 = Distance(points_[0], points_[1]);
    double base2 = Distance(points_[2], points_[3]);
    double height = std::fabs(points_[0].y - points_[2].y);
    return 0.5 * (base1 + base2) * height;
}
Trapezoid::operator double() const {
    return Area();
}
Trapezoid::~Trapezoid() {
    delete[] points_;
}
bool Trapezoid::Validate(Point p1, Point p2, Point p3, Point p4) const {
    Point points_arr[TRAPEZOIDANGLES] = {p1, p2, p3, p4};
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        for (size_t j = i + 1; j != TRAPEZOIDANGLES; ++j) {
            if (points_arr[i] == points_arr[j]) {
                return false;
            }
        }
    }
    double vec1_x = p2.x - p1.x; 
    double vec1_y = p2.y - p1.y;
    double vec2_x = p4.x - p3.x;
    double vec2_y = p4.y - p3.y;
    double cross = vec1_x * vec2_y - vec1_y * vec2_x;

    double vec3_x = p3.x - p2.x;
    double vec3_y = p3.y - p2.y;
    double vec4_x = p1.x - p4.x;
    double vec4_y = p1.y - p4.y;
    double cross2 = vec3_x * vec4_y - vec3_y * vec4_x;

    bool is_sides_parallel = (std::fabs(cross) < EPS) || (std::fabs(cross2) < EPS);
    double base1 = Distance(p1, p2);
    double base2 = Distance(p3, p4);
    double height = std::fabs(p1.y - p3.y);
    double temp_area = 0.5 * (base1 + base2) * height;
    
    return is_sides_parallel && temp_area > EPS;
}

bool operator==(const Trapezoid& d1, const Trapezoid& d2) {
    double d1_side = Distance(d1.points_[0], d1.points_[1]);
    double d2_side = Distance(d2.points_[0], d2.points_[1]);
    return (d1_side == d2_side && d1.Area() - d2.Area() < EPS);
}
bool operator!=(const Trapezoid& d1, const Trapezoid& d2) {
    return !(d1 == d2);
}
std::ostream& operator<<(std::ostream& os, const Trapezoid& d) {
    os << "[";
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        os << d.points_[i];
    }
    os << "]" << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, Trapezoid& d) {
    Point input_points[TRAPEZOIDANGLES];
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        is >> input_points[i];
    }
    try {
        Trapezoid tmp(input_points[0], input_points[1], input_points[2], input_points[3]);
        std::swap(d.points_, tmp.points_);
    } catch (exceptions::InvalidPointsException& e) {
        std::cerr << "Diamond: Wrong points from input" << std::endl;
        return is;
    }
    return is;
}
}