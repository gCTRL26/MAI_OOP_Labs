#pragma once

#include "vector.hpp"
#include "exception.hpp"

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <memory>

namespace vector {

template<class T>
Vector<T>::Vector() : sz_(0), cap_(0), arr_(nullptr) {}

template<class T>
Vector<T>::Vector(size_t n) : sz_(n), cap_(n), arr_(std::make_shared<T[]>(cap_)) {}

template<class T>
Vector<T>::Vector(size_t n, const T& val) : sz_(n), cap_(n), arr_(std::make_shared<T[]>(cap_)) {
    for (size_t i = 0; i != sz_; ++i) {
        arr_[i] = val;
    }
}

template<class T>
Vector<T>::Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_), arr_(std::make_shared<T[]>(cap_)) {
    std::copy(other.arr_.get(), other.arr_.get() + sz_, arr_.get());
}

template<class T>
Vector<T>::Vector(Vector&& other) noexcept : sz_(other.sz_), cap_(other.cap_), arr_(std::move(other.arr_)) {
    other.sz_ = 0;
    other.cap_ = 0;
}

template<class T>
Vector<T>::Vector(std::initializer_list<T> init) : sz_(init.size()), cap_(init.size()), arr_(std::make_shared<T[]>(cap_)) {
    size_t i = 0;
    for (const T& item : init) {
        arr_[i++] = item;
    }
}

template<class T>
T& Vector<T>::operator[](size_t pos) {
    return arr_[pos];
}

template<class T>
const T& Vector<T>::operator[](size_t pos) const {
    return arr_[pos];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    Vector temp = other;
    Swap(temp);
    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    Vector temp = std::move(other);
    other.sz_ = 0;
    other.cap_ = 0;
    Swap(temp);
    return *this;
}

template<class T>
T& Vector<T>::Front() const {
    if (IsEmpty()) {
        throw exceptions::VectorOutOfRange("Out of range!");
    }
    return arr_[0];
}

template<class T>
T& Vector<T>::Back() const {
    if (IsEmpty()) {
        throw exceptions::VectorOutOfRange("Out of range!");
    }
    return arr_[sz_ - 1];
}

template<class T>
T* Vector<T>::Data() const noexcept {
    return arr_.get();
}

template<class T>
bool Vector<T>::IsEmpty() const noexcept {
    return sz_ == 0;
}

template<class T>
size_t Vector<T>::Size() const noexcept {
    return sz_;
}

template<class T>
size_t Vector<T>::Capacity() const noexcept {
    return cap_;
}

template<class T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap <= cap_) {
        return;
    }
    std::shared_ptr<T[]> new_arr = std::make_shared<T[]>(new_cap);

    for (size_t i = 0; i != sz_; ++i) {
        new_arr[i] = std::move(arr_[i]);
    }
    arr_ = std::move(new_arr);
    cap_ = new_cap;
}

template<class T>
void Vector<T>::Clear() noexcept {
    arr_.reset();
    sz_ = 0;
    cap_ = 0;
}

template<class T>
void Vector<T>::Insert(size_t pos, const T& value) {
    if (pos > sz_) {
        return;
    }

    if (sz_ == cap_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }

    if (pos == sz_) {
        PushBack(std::move(value));
        return;
    }

    for (size_t i = sz_; i > pos; --i) {
        arr_[i] = std::move(arr_[i - 1]);
    }
    arr_[pos] = value;
    ++sz_; 
}

template<class T>
void Vector<T>::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos > end_pos || end_pos > sz_) {
        return;
    }

    for (size_t i = end_pos; i != sz_; ++i) {
        arr_[begin_pos - end_pos + i] = std::move(arr_[i]);
    }
    sz_ -= (end_pos - begin_pos);
}

template<class T>
void Vector<T>::PushBack(const T& value) {
    if (sz_ == cap_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }
    arr_[sz_++] = value;
}

template<class T>
void Vector<T>::PopBack() {
    if (sz_ == 0) {
        throw exceptions::VectorOutOfRange("Out of range!");
    }
    --sz_;
}

template<class T>
template<class U>
U Vector<T>::TotalArea() {
    U res = 0.0;
    for (size_t i = 0; i != sz_; ++i) {
        res += arr_[i]->Area();
    }
    return res;
}

template<class T>
void Vector<T>::SeparateCenter() {
    for (size_t i = 0; i != sz_; ++i) {
        std::cout << "Figure " << i + 1 << " center is" << arr_[i]->Center() << std::endl;
    }
}

template<class T>
void Vector<T>::SeparateArea() {
    for (size_t i = 0; i != sz_; ++i) {
        std::cout << "Figure " << i + 1 << " area is" << arr_[i]->Area() << std::endl;
    }
}

template<class T>
void Vector<T>::Swap(Vector& other) noexcept {
    std::swap(sz_, other.sz_);
    std::swap(cap_, other.cap_);
    std::swap(arr_, other.arr_);
}
}