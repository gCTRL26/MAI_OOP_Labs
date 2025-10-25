#pragma once
#include <iostream>

namespace figure {
    constexpr const double EPS = 1e-9;
    constexpr const int ANGLES = 4;

    class Point {
      public:
        double x = 0.0;
        double y = 0.0;
        Point() = default;
        Point(double x, double y);
    };

    bool operator==(const Point& p1, const Point& p2);
    bool operator!=(const Point& p1, const Point& p2);

    class Figure {
      public:
        virtual Point Center() const = 0;
        virtual operator double() const = 0;
        virtual double Area() const = 0;
        virtual ~Figure() = default;
    };

    double Distance(const Point& p1, const Point& p2);

    std::ostream& operator<<(std::ostream& os, const Point& p);
    std::istream& operator>>(std::istream& is, Point& p);
}