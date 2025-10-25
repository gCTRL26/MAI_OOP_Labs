#include <cmath>
#include <cstddef>

#include "rectangle.hpp"
#include "exception.hpp"

namespace figure {
    Rectangle::Rectangle(): Rectangle(Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)) {}
    Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
        if (!Validate(p1, p2, p3, p4)) {
            throw exceptions::InvalidPointsException("Rectangle: Wrong points");
        }
        points_ = new Point[ANGLES] {p1, p2, p3, p4};
    }
    Rectangle::Rectangle(const Rectangle& other) {
        points_ = new Point[ANGLES];
        for (size_t i = 0; i != ANGLES; ++i) {
            points_[i] = Point(other.points_[i].x, other.points_[i].y);
        }
    }
    Rectangle& Rectangle::operator=(const Rectangle& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i != ANGLES; ++i) {
            points_[i] = other.points_[i];
        }
        return *this;
    }
    Point Rectangle::Center() const {
        Point p_c((points_[0].x + points_[2].x) / 2.0, (points_[0].y + points_[2].y) / 2.0);
        return p_c;
    }
    double Rectangle::Area() const {
        return Distance(points_[0], points_[1]) * Distance(points_[1], points_[2]);
    }
    Rectangle::operator double() const {
        return Area();
    }
    Rectangle::~Rectangle() {
        delete [] points_;
    }
    bool Rectangle::Validate(Point p1, Point p2, Point p3, Point p4) const {
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

        double dot = (p2.x - p1.x) * (p3.x - p2.x) + (p2.y - p1.y) * (p3.y - p2.y);

        double tmp_area = side1 * side2;

        return (std::fabs(side1 - side3) < EPS && 
                std::fabs(side2 - side4) < EPS &&
                std::fabs(dot) < EPS && 
                tmp_area > EPS);
    }

    bool operator==(const Rectangle& r1, const Rectangle& r2) {
        double r1_side = Distance(r1.points_[0], r1.points_[1]);
        double r2_side = Distance(r2.points_[0], r2.points_[1]);
        return (r1_side == r2_side && r1.Area() - r2.Area() < EPS);
    }
    bool operator!=(const Rectangle& r1, const Rectangle& r2) {
        return !(r1 == r2);
    }
    std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
        os << "[";
        for (size_t i = 0; i != ANGLES; ++i) {
            os << "(" << r.points_[i].x << ", " << r.points_[i].y << ")";
        }
        os << "]" << std::endl;
        return os;
    }
    std::istream& operator>>(std::istream& is, Rectangle& r) {
        Point input_points[ANGLES];
        for (size_t i = 0; i != ANGLES; ++i) {
            is >> input_points[i];
        }
        try {
            Rectangle tmp(input_points[0], input_points[1], input_points[2], input_points[3]);
            std::swap(r.points_, tmp.points_);
        } catch (exceptions::InvalidPointsException& e) {
            std::cerr << "Rectangle: Wrong points from input" << std::endl;
            return is;
        }
        return is;
    }
}