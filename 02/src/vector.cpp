#include "../include/vector.hpp"

// vector realization

namespace vector {
    const int START_CAP = 10;

    Vector::Vector() : arr_(nullptr), sz_(0), cap_(0) {
    }

    Vector::Vector(size_t count, const unsigned char& value) : arr_(new unsigned char[count]), sz_(count), cap_(count) {
        for (size_t i = 0; i != count; ++i) {
            new (arr_ + i) unsigned char(std::move(value));
        }
    }

    Vector::Vector(const Vector& other)
        : arr_(reinterpret_cast<unsigned char*>(new int8_t[other.cap_ * sizeof(unsigned char)])), sz_(other.sz_), cap_(other.cap_) {
        for (size_t i = 0; i != sz_; ++i) {
            new (arr_ + i) unsigned char(std::move(other.arr_[i]));
        }
    }

    Vector::Vector(Vector&& other) noexcept : arr_(other.arr_), sz_(other.sz_), cap_(other.cap_) {
        other.arr_ = nullptr;
        other.sz_ = 0;
        other.cap_ = 0;
    }

    Vector::Vector(std::initializer_list<unsigned char> init)
        : arr_(reinterpret_cast<unsigned char*>(new int8_t[init.size() * sizeof(unsigned char)])),
        sz_(init.size()),
        cap_(init.size() < START_CAP ? START_CAP : init.size()) {
        size_t i = 0;
        for (const unsigned char& val : init) {
            new (arr_ + i) unsigned char(std::move(val));
            ++i;
        }
    }

    unsigned char& Vector::Front() const noexcept {
        return arr_[0];
    }

    bool Vector::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    unsigned char& Vector::Back() const noexcept {
        return arr_[sz_ - 1];
    }

    unsigned char* Vector::Data() const noexcept {
        return arr_;
    }

    unsigned char& Vector::Get(size_t pos) {
        return arr_[pos];
    }

    unsigned char Vector::Get(size_t pos) const {
        return arr_[pos];
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
        unsigned char* new_arr = reinterpret_cast<unsigned char*>(new int8_t[new_cap * sizeof(unsigned char)]);
        
        for (size_t i = 0; i != sz_; ++i) {
            new (new_arr + i) unsigned char(std::move(arr_[i]));
        }
        delete[] reinterpret_cast<int8_t*>(arr_);
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void Vector::Clear() noexcept {
        delete[] reinterpret_cast<int8_t*>(arr_);
        arr_ = nullptr;
        sz_ = 0;
        cap_ = 0;
    }

    void Vector::Insert(size_t pos, unsigned char value) {
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
            new (arr_ + i) unsigned char(std::move(arr_[i - 1]));
        }
        new (arr_ + pos) unsigned char(std::move(value));
        ++sz_;
    }

    void Vector::Erase(size_t begin_pos, size_t end_pos) {
        if (begin_pos > end_pos || end_pos > sz_) {
            return;
        }

        for (size_t i = end_pos; i != sz_; ++i) {
            new (arr_ + begin_pos - end_pos + i) unsigned char(std::move(arr_[i]));
        }
        sz_ -= (end_pos - begin_pos);
    }

    void Vector::PushBack(unsigned char value) {
        if (cap_ == sz_) {
            Reserve(cap_ == 0 ? START_CAP : cap_ * 2);
        }
        new (arr_ + sz_) unsigned char(std::move(value));
        ++sz_;
    }

    void Vector::PopBack() {
        if (sz_ > 0) {
            --sz_;
        }
    }

    void Vector::Resize(size_t count, const unsigned char& value) {
        if (count > cap_) {
            Reserve(count);
        } 
        for (size_t i = sz_; i != count; ++i) {
            new (arr_ + i) unsigned char(std::move(value));
        }
        sz_ = count;
    }

    Vector& Vector::Copy(const Vector& other) {
        if (&other == this) {
            return *this;
        }
        Vector tmp = other;
        Swap(tmp);
        return *this;
    }

    Vector::~Vector() {
        delete[] reinterpret_cast<int8_t*>(arr_);
    }
}
