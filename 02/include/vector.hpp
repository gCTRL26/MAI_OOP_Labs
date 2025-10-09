#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace vector {
    class Vector {
    public:
        Vector();

        Vector(size_t count, const unsigned char& value);

        Vector(const Vector& other);

        Vector(Vector&& other) noexcept;

        Vector(std::initializer_list<unsigned char> init);

        unsigned char& Front() const noexcept;

        unsigned char& Back() const noexcept;

        unsigned char* Data() const noexcept;

        unsigned char& Get(size_t pos);

        unsigned char Get(size_t pos) const;

        bool IsEmpty() const noexcept;

        size_t Size() const noexcept;

        size_t Capacity() const noexcept;

        void Reserve(size_t new_cap);

        void Clear() noexcept;

        void Insert(size_t pos, unsigned char value);

        void Erase(size_t begin_pos, size_t end_pos);

        void PushBack(unsigned char value);

        void PopBack();

        void Resize(size_t count, const unsigned char& value);

        Vector& Copy(const Vector& other);

        ~Vector();

    private:
        unsigned char* arr_;
        size_t sz_;
        size_t cap_;

        void Swap(Vector& other) {
            std::swap(other.arr_, arr_);
            std::swap(other.cap_, cap_);
            std::swap(other.sz_, sz_);
        }
    };
}
