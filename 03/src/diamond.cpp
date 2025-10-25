#include <cmath>
#include <cstddef>
#include <iostream>
#include <utility>

#include "diamond.hpp"
#include "exception.hpp"

namespace figure {
    Diamond::Diamond(): Diamond(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)) {}
    Diamond::Diamond(Point p1, Point p2, Point p3, Point p4) {
        if (!Validate(p1, p2, p3, p4)) {
            throw exceptions::InvalidPointsException("Diamond: Wrong points");
        }
        points_ = new Point[ANGLES] {p1, p2, p3, p4};
    }
    Diamond::Diamond(const Diamond& other) {
        points_ = new Point[ANGLES];
        for (size_t i = 0; i != ANGLES; ++i) {
            points_[i] = Point(other.points_[i].x, other.points_[i].y);
        }
    }
    Diamond& Diamond::operator=(const Diamond& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i != ANGLES; ++i) {
            points_[i] = other.points_[i];
        }
        return *this;
    }
    Point Diamond::Center() const {
        Point p_c((points_[0].x + points_[2].x) / 2.0, (points_[0].y + points_[2].y) / 2.0);
        return p_c;
    }
    double Diamond::Area() const {
        double d1 = Distance(points_[0], points_[2]);
        double d2 = Distance(points_[1], points_[3]);
        return (d1 * d2) / 2.0;
    }
    Diamond::operator double() const {
        return Area();
    }
    Diamond::~Diamond() {
        delete [] points_;
    }
    bool Diamond::Validate(Point p1, Point p2, Point p3, Point p4) const {
        Point points_arr[ANGLES] = {p1, p2, p3, p4};
        for (size_t i = 0; i != ANGLES; ++i) {
            for (size_t j = i + 1; j != ANGLES; ++j) {
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

    bool operator==(const Diamond& d1, const Diamond& d2) {
        double d1_side = Distance(d1.points_[0], d1.points_[1]);
        double d2_side = Distance(d2.points_[0], d2.points_[1]);
        return (d1_side == d2_side && d1.Area() - d2.Area() < EPS);
    }
    bool operator!=(const Diamond& d1, const Diamond& d2) {
        return !(d1 == d2);
    }
    std::ostream& operator<<(std::ostream& os, const Diamond& d) {
        os << "[";
        for (size_t i = 0; i != ANGLES; ++i) {
            os << "(" << d.points_[i].x << ", " << d.points_[i].y << ")";
        }
        os << "]" << std::endl;
        return os;
    }
    std::istream& operator>>(std::istream& is, Diamond& d) {
        Point input_points[ANGLES];
        for (size_t i = 0; i != ANGLES; ++i) {
            is >> input_points[i];
        }
        try {
            Diamond tmp(input_points[0], input_points[1], input_points[2], input_points[3]);
            std::swap(d.points_, tmp.points_);
        } catch (exceptions::InvalidPointsException& e) {
            std::cerr << "Diamond: Wrong points from input" << std::endl;
            return is;
        }
        return is;
    }
}