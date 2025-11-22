#pragma once

#include "exceptions.hpp"
#include "vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory_resource>

namespace vector {
template<class T>
Vector<T>::ForwardVectorIterator::ForwardVectorIterator(T* ptr) : ptr_(ptr) {}

template<class T>
bool Vector<T>::ForwardVectorIterator::operator==(const ForwardVectorIterator& it) const {
    return ptr_ == it.ptr_;
}

template<class T>
bool Vector<T>::ForwardVectorIterator::operator!=(const ForwardVectorIterator& it) const {
    return !(ptr_ == it.ptr_);
}

template<class T>
typename Vector<T>::ForwardVectorIterator::reference_type Vector<T>::ForwardVectorIterator::operator*() const {
    return *ptr_;
}

template<class T>
typename Vector<T>::ForwardVectorIterator::pointer_type Vector<T>::ForwardVectorIterator::operator->() const {
    return ptr_;
}

template<class T>
typename Vector<T>::ForwardVectorIterator& Vector<T>::ForwardVectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template<class T>
typename Vector<T>::ForwardVectorIterator Vector<T>::ForwardVectorIterator::operator++(int) {
    ForwardVectorIterator tmp = *this;
    ++ptr_;
    return tmp;
}

template<class T>
Vector<T>::Vector(std::pmr::memory_resource* mr) : allocator_(mr), arr_(nullptr), sz_(0), cap_(0) {}

template<class T>
Vector<T>::Vector(size_t count, const T& val, std::pmr::memory_resource* mr) : allocator_(mr), sz_(count), cap_(count) {
    arr_ = allocator_.allocate(count);
    for (size_t i = 0; i != count; ++i) {
        allocator_.construct(arr_ + i, val);
    }
}

template<class T>
Vector<T>::Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_), allocator_(other.allocator_) {
    if (other.sz_ > 0) {
        arr_ = allocator_.allocate(sz_);
        for (size_t i = 0; i != sz_; ++i) {
            allocator_.construct(arr_ + i, other.arr_[i]);
        }
    } else {
        arr_ = nullptr;
    }
}

template<class T>
Vector<T>::Vector(Vector&& other) noexcept : arr_(other.arr_), sz_(other.sz_), cap_(other.cap_), allocator_(other.allocator_) {
    other.arr_ = nullptr;
    other.sz_ = 0;
    other.cap_ = 0;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        for (size_t i = 0; i != sz_; ++i) {
            allocator_.destroy(arr_ + i);
        }

        if (other.sz_ > cap_) {
            if (arr_) {
                allocator_.deallocate(arr_, cap_);
            }
            arr_ = allocator_.allocate(other.sz_);
            cap_ = other.sz_;
        }

        for (size_t i = 0; i != other.sz_; ++i) {
            allocator_.construct(arr_ + i, other.arr_[i]);
        }

        sz_ = other.sz_;
    }

    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i != sz_; ++i) {
            allocator_.destroy(arr_ + i);
        }
        if (arr_) {
            allocator_.deallocate(arr_, cap_);
        }

        arr_ = other.arr_;
        sz_ = other.sz_;
        cap_ = other.cap_;

        other.arr_ = nullptr;
        other.sz_ = 0;
        other.cap_ = 0;
    }

    return *this;
}

template<class T>
Vector<T>::Vector(std::initializer_list<T> init, std::pmr::memory_resource* mr)
    : sz_(init.size()), cap_(init.size()), allocator_(mr) {
        if (init.size() > 0) {
            arr_ = allocator_.allocate(init.size());
            size_t i = 0;
            for (const auto& it : init) {
                allocator_.construct(arr_ + i, it);
                ++i;
            }
        } else {
            arr_ = nullptr;
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
typename Vector<T>::ForwardVectorIterator Vector<T>::Begin() const noexcept {
    return ForwardVectorIterator(arr_);
}

template<class T>
typename Vector<T>::ForwardVectorIterator Vector<T>::End() const noexcept {
    return ForwardVectorIterator(arr_ + sz_);
}

template<class T>
T& Vector<T>::Front() const {
    if (sz_ == 0 ) {
        throw exceptions::VectorOutOfRange("Vector is empty");
    }
    return arr_[0];
}

template<class T>
T& Vector<T>::Back() const {
    if (sz_ == 0) {
        throw exceptions::VectorOutOfRange("Vector is empty");
    }
    return arr_[sz_ - 1];
}

template<class T>
T* Vector<T>::Data() const noexcept {
    return arr_;
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
    if (new_cap < cap_) {
        return;
    }

    T* new_arr = allocator_.allocate(new_cap);
    for (size_t i = 0; i != sz_; ++i) {
        allocator_.construct(new_arr + i, std::move(arr_[i]));
        allocator_.destroy(arr_ + i);
    }
    if (arr_) {
        allocator_.deallocate(arr_, cap_);
    }
    arr_ = new_arr;
    cap_ = new_cap;
}

template<class T>
void Vector<T>::Clear() noexcept {
    for (size_t i = 0; i != sz_; ++i) {
        allocator_.destroy(arr_ + i);
    }
    sz_ = 0;
}

template<class T>
void Vector<T>::Insert(size_t pos, T value) {
    if (pos > sz_) {
        return;
    }

    if (sz_ == cap_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }

    for (size_t i = sz_; i > pos; --i) {
        allocator_.construct(arr_ + i, std::move(arr_[i - 1]));
        allocator_.destroy(arr_ + i - 1);
    }

    allocator_.construct(arr_ + pos, std::move(value));
    ++sz_;
}
template<class T>
void Vector<T>::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos > end_pos || end_pos > sz_) {
        return;
    }

    for (size_t i = begin_pos; i != end_pos; ++i) {
        allocator_.destroy(arr_ + i);
    }

    for (size_t i = end_pos; i != sz_; ++i) {
        allocator_.construct(arr_ + begin_pos - end_pos + i, std::move(arr_[i]));
        allocator_.destroy(arr_ + i);
    }
    sz_ -= (end_pos - begin_pos);
}

template<class T>
void Vector<T>::PushBack(T value) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }
    
    allocator_.construct(arr_ + sz_, std::move(value));
    ++sz_;
}

template<class T>
template <class... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
    }
    
    allocator_.construct(arr_ + sz_, std::forward<Args>(args)...);
    ++sz_;
}

template<class T>
void Vector<T>::PopBack() {
    if (sz_ > 0) {
        --sz_;
        allocator_.destroy(arr_ + sz_);
    }
}

template<class T>
void Vector<T>::Resize(size_t count, const T& value) {
    if (count > cap_) {
        Reserve(count);
        for (size_t i = sz_; i != count; ++i) {
            allocator_.construct(arr_ + i, std::move(value));
        }
    } else if (count < cap_) {
        for (size_t i = count; i != sz_; ++i) {
            allocator_.destroy(arr_ + i);
        }
    }
    sz_ = count;
}

template<class T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < sz_; ++i) {
        allocator_.destroy(arr_ + i);
    }
    if (arr_) {
        allocator_.deallocate(arr_, cap_);
    }
}
}