#pragma once

#include "figure.hpp"

namespace figure {
    class Diamond : public Figure {
        friend bool operator==(const Diamond& d1, const Diamond& d2);
        friend bool operator!=(const Diamond& d1, const Diamond& d2);
        friend std::ostream& operator<<(std::ostream& os, const Diamond& d);
        friend std::istream& operator>>(std::istream& is, Diamond& d);
      private:
        Point* points_;
        bool Validate(Point p1, Point p2, Point p3, Point p4) const;
      public:
        Diamond();
        Diamond(Point p1, Point p2, Point p3, Point p4);
        Diamond(const Diamond& other);
        Diamond& operator=(const Diamond& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Diamond();
    };

    bool operator==(const Diamond& d1, const Diamond& d2);
    bool operator!=(const Diamond& d1, const Diamond& d2);
    std::ostream& operator<<(std::ostream& os, const Diamond& d);
    std::istream& operator>>(std::istream& is, const Diamond& d);
}