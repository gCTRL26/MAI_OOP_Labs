#pragma once

#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <memory>

namespace vector {
const size_t START_CAP = 4;
template<class T>
class Vector {
    public:
    Vector();
    Vector(size_t n);
    Vector(size_t n, const T& val);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> init);
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    T& Front() const;
    T& Back() const;
    T* Data() const noexcept;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    void Reserve(size_t new_cap);
    void Clear() noexcept;
    void Insert(size_t pos, const T& value);
    void Erase(size_t begin_pos, size_t end_pos);
    void PushBack(const T& value);
    void PopBack();

    template<class U>
    U TotalArea();
    void SeparateCenter();
    void SeparateArea();

    ~Vector() = default;

private:
    size_t sz_;
    size_t cap_;
    std::shared_ptr<T[]> arr_;
    inline static void Deleter(T* ptr) {
        if (ptr) {
            delete[] ptr;
        }
    }
    void Swap(Vector& other) noexcept;
};
}

#include "vector.ipp"