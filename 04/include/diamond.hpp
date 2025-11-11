#pragma once

#include "figure.hpp"
#include <memory>

namespace figure {
template<Arithmetic T>
class Diamond : public Figure<T> {
    template<Arithmetic U>
    friend bool operator==(const Diamond<U>& d1, const Diamond<U>& d2);
    template<Arithmetic U>
    friend bool operator!=(const Diamond<U>& d1, const Diamond<U>& d2);
    template<Arithmetic U>
    friend std::ostream& operator<<(std::ostream& os, const Diamond<U>& d);
    template<Arithmetic U>
    friend std::istream& operator>>(std::istream& is, Diamond<U>& d);
  private:
    std::unique_ptr<Point<T>[]> points_;
    bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const;
  public:
    Diamond();
    Diamond(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
    Diamond(const Diamond<T>& other);
    Diamond<T>& operator=(const Diamond<T>& other);
    Point<T> Center() const override;
    double Area() const override;
    operator double() const override;
    ~Diamond() override = default;
};

template<Arithmetic T>
bool operator==(const Diamond<T>& d1, const Diamond<T>& d2);

template<Arithmetic T>
bool operator!=(const Diamond<T>& d1, const Diamond<T>& d2);

template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Diamond<T>& d);

template<Arithmetic T>
std::istream& operator>>(std::istream& is, Diamond<T>& d);
}

#include "diamond.ipp"