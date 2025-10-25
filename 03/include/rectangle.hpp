#pragma once

#include "figure.hpp"

namespace figure {
    class Rectangle : public Figure {
        friend bool operator==(const Rectangle& d1, const Rectangle& d2);
        friend bool operator!=(const Rectangle& d1, const Rectangle& d2);
        friend std::ostream& operator<<(std::ostream& os, const Rectangle& d);
        friend std::istream& operator>>(std::istream& is, Rectangle& d);
      private:
        Point* points_;
        bool Validate(Point p1, Point p2, Point p3, Point p4) const;
      public:
        Rectangle();
        Rectangle(Point p1, Point p2, Point p3, Point p4);
        Rectangle(const Rectangle& other);
        Rectangle& operator=(const Rectangle& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Rectangle();
    };

    bool operator==(const Rectangle& d1, const Rectangle& d2);
    bool operator!=(const Rectangle& d1, const Rectangle& d2);
    std::ostream& operator<<(std::ostream& os, const Rectangle& d);
    std::istream& operator>>(std::istream& is, const Rectangle& d);
}