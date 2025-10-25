#include <cstddef>
#include <iostream>
#include <utility>
#include <memory>

#include "vector.hpp"

namespace vector {
    const size_t START_CAP = 4;
    
    Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {}

    Vector::Vector(std::initializer_list<figure::Figure*> init) : sz_(init.size()), cap_(init.size()) {
        arr_ = new figure::Figure*[init.size()];
        size_t i = 0;
        for (auto f : init) {
            arr_[i] = f;
            ++i;
        }
    } 

    Vector::Vector(const Vector& other): cap_(other.cap_), sz_(other.sz_), arr_(new figure::Figure*[cap_]) {
        std::uninitialized_copy(other.arr_, other.arr_ + other.sz_, arr_);
    }

    Vector::Vector(Vector&& other) noexcept: cap_(other.cap_), sz_(other.sz_), arr_(other.arr_)  {
        other.cap_ = 0;
        other.sz_= 0;
        other.arr_ = nullptr;
    }

    figure::Figure& Vector::operator[](size_t pos) {
        return *arr_[pos];
    }

    const figure::Figure& Vector::operator[](size_t pos) const {
        return *arr_[pos];
    }

    Vector& Vector::operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Vector temp = other;
        Swap(temp);
        return *this;   
    }

    Vector& Vector::operator=(Vector&& other) noexcept {
            if (this == &other) {
            return *this;
        }
        Vector temp = std::move(other);
        Swap(temp);
        return *this;
    }

    figure::Figure& Vector::Front() const noexcept {
        return *arr_[0];
    }

    figure::Figure& Vector::Back() const noexcept {
        return *arr_[sz_ - 1];
    }

    figure::Figure** Vector::Data() const noexcept {
        return arr_;
    }

    bool Vector::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    size_t Vector::Size() const noexcept {
        return sz_;
    }

    size_t Vector::Capacity() const noexcept {
        return cap_;
    }

    void Vector::Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
        return;
        }
        figure::Figure** new_arr = reinterpret_cast<figure::Figure**>(new int8_t[new_cap * sizeof(figure::Figure*)]);

        for (size_t i = 0; i != sz_; ++i) {
            new_arr[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void Vector::Clear() noexcept {
        delete [] arr_;
        arr_ = nullptr;
        sz_ = 0;
    }

    void Vector::Insert(size_t pos, figure::Figure* value) {
        if (pos > sz_) {
            return;
        }

        if (sz_ == cap_) {
            Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
        }

        if (pos == sz_) {
            PushBack(value);
            return;
        }

        for (size_t i = sz_; i > pos; --i) {
            arr_[i] = arr_[i - 1];
        }
        arr_[pos] = value;
        ++sz_;    
    }

    void Vector::Erase(size_t begin_pos, size_t end_pos) {
        if (begin_pos > end_pos || end_pos > sz_) {
            return;
        }

        for (size_t i = end_pos; i != sz_; ++i) {
            arr_[begin_pos - end_pos + i] = arr_[i];
        }
        sz_ -= (end_pos - begin_pos);
    }

    void Vector::PushBack(figure::Figure* value) {
    if (cap_ == sz_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }
    arr_[sz_] = value;
    ++sz_;
    }

    void Vector::PopBack() {
        --sz_;
    }

    double Vector::TotalArea() {
        double res = 0.0;
        for (size_t i = 0; i != sz_; ++i) {
            res += arr_[i]->Area();
        }

        return res;
    }

    void Vector::SeparateCenter() {
        for (size_t i = 0; i != sz_; ++i) {
            std::cout << "Figure " << i + 1 << " center is" << arr_[i]->Center() << std::endl;
        }
    }

    void Vector::SeparateArea() {
        for (size_t i = 0; i != sz_; ++i) {
            std::cout << "Figure " << i + 1 << " area is" << arr_[i]->Area() << std::endl;
        }
    }

    void Vector::Swap(Vector& other) noexcept {
        std::swap(sz_, other.sz_);
        std::swap(cap_, other.cap_);
        std::swap(arr_, other.arr_);
    }

    Vector::~Vector() {
        delete [] arr_;
    }
}