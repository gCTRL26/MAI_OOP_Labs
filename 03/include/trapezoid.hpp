#pragma once

#include "figure.hpp"

namespace figure {
    class Trapezoid : public Figure {
        friend bool operator==(const Trapezoid& d1, const Trapezoid& d2);
        friend bool operator!=(const Trapezoid& d1, const Trapezoid& d2);
        friend std::ostream& operator<<(std::ostream& os, const Trapezoid& d);
        friend std::istream& operator>>(std::istream& is, Trapezoid& d);
      private:
        Point* points_;
        bool Validate(Point p1, Point p2, Point p3, Point p4) const;
      public:
        Trapezoid();
        Trapezoid(Point p1, Point p2, Point p3, Point p4);
        Trapezoid(const Trapezoid& other);
        Trapezoid& operator=(const Trapezoid& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Trapezoid();
    };

    bool operator==(const Trapezoid& d1, const Trapezoid& d2);
    bool operator!=(const Trapezoid& d1, const Trapezoid& d2);
    std::ostream& operator<<(std::ostream& os, const Trapezoid& d);
    std::istream& operator>>(std::istream& is, const Trapezoid& d);
}