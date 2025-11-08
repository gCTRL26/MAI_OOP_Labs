#pragma once

#include "figure.hpp"
#include <memory>

namespace figure {
template<Arithmetic T>
class Hexagon : public Figure<T> {
    template<Arithmetic U>
    friend bool operator==(const Hexagon<U>& h1, const Hexagon<U>& h2);
    template<Arithmetic U>
    friend bool operator!=(const Hexagon<U>& h1, const Hexagon<U>& h2);
    template<Arithmetic U>
    friend std::ostream& operator<<(std::ostream& os, const Hexagon<U>& h);
    template<Arithmetic U>
    friend std::istream& operator>>(std::istream& is, Hexagon<U>& h);
  private:
    std::unique_ptr<Point<T>[]> points_;
    bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5, const Point<T>& p6) const;
  public:
    Hexagon();
    Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5, const Point<T>& p6);
    Hexagon(const Hexagon<T>& other);
    Hexagon<T>& operator=(const Hexagon<T>& other);
    Point<T> Center() const override;
    double Area() const override;
    operator double() const override;
    ~Hexagon() override = default;
};

template<Arithmetic T>
bool operator==(const Hexagon<T>& h1, const Hexagon<T>& h2);

template<Arithmetic T>
bool operator!=(const Hexagon<T>& h1, const Hexagon<T>& h2);

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Hexagon<T>& h);

template<Arithmetic T>
std::istream& operator>>(std::istream& is, Hexagon<T>& h);
}

#include "hexagon.ipp"