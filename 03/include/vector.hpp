#pragma once

#include "figure.hpp"

#include <cstdlib>
#include <initializer_list>

namespace vector {
class Vector {
    friend void swap(Vector& v1, Vector& v2) noexcept;
    public:
    Vector();

    Vector(const Vector& other);

    Vector(Vector&& other) noexcept;

    Vector(std::initializer_list<figure::Figure*> init);

    figure::Figure& operator[](size_t pos);

    const figure::Figure& operator[](size_t pos) const;

    Vector& operator=(const Vector& other);

    Vector& operator=(Vector&& other) noexcept;

    figure::Figure& Front() const;

    figure::Figure& Back() const;

    figure::Figure** Data() const noexcept;

    bool IsEmpty() const noexcept;

    size_t Size() const noexcept;

    size_t Capacity() const noexcept;

    void Reserve(size_t new_cap);

    void Clear() noexcept;

    void Insert(size_t pos, figure::Figure* value);

    void Erase(size_t begin_pos, size_t end_pos);

    void PushBack(figure::Figure* value);

    void PopBack();

    double TotalArea();

    void SeparateCenter();

    void SeparateArea();

    ~Vector();

private:
    size_t sz_;
    size_t cap_;
    figure::Figure** arr_;
    void Swap(Vector& other) noexcept;
};
}