#pragma once

#include "figure.hpp"
#include <memory>

namespace figure {
template<Arithmetic T>
class Pentagon : public Figure<T> {
    template<Arithmetic U>
    friend bool operator==(const Pentagon<U>& pen1, const Pentagon<U>& pen2);
    template<Arithmetic U>
    friend bool operator!=(const Pentagon<U>& pen1, const Pentagon<U>& pen2);
    template<Arithmetic U>
    friend std::ostream& operator<<(std::ostream& os, const Pentagon<U>& p);
    template<Arithmetic U>
    friend std::istream& operator>>(std::istream& is, Pentagon<U>& p);
  private:
    std::unique_ptr<Point<T>[]> points_;
    bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5) const;
  public:
    Pentagon();
    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5);
    Pentagon(const Pentagon<T>& other);
    Pentagon<T>& operator=(const Pentagon<T>& other);
    Point<T> Center() const override;
    double Area() const override;
    operator double() const override;
    ~Pentagon() override = default;
};

template<Arithmetic T>
bool operator==(const Pentagon<T>& pen1, const Pentagon<T>& pen2);

template<Arithmetic T>
bool operator!=(const Pentagon<T>& pen1, const Pentagon<T>& pen2);

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Pentagon<T>& p);

template<Arithmetic T>
std::istream& operator>>(std::istream& is, Pentagon<T>& p);
}

#include "pentagon.ipp"