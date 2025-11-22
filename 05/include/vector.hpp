#pragma once

#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iterator>
#include <memory_resource>

namespace vector {
const size_t START_CAP = 4;
template <typename T>
class Vector {
public:
    class ForwardVectorIterator {
        friend class Vector;
      private:
        T* ptr_;
        explicit ForwardVectorIterator(T* ptr);
      public:
        using value_type = T;
        using reference_type = value_type&;
        using pointer_type = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_type = std::forward_iterator_tag;

        bool operator==(const ForwardVectorIterator& it) const;
        bool operator!=(const ForwardVectorIterator& it) const;
        reference_type operator*() const;
        pointer_type operator->() const;
        ForwardVectorIterator& operator++();
        ForwardVectorIterator operator++(int);
    };

    explicit Vector(std::pmr::memory_resource* mr = std::pmr::get_default_resource());

    Vector(size_t count, const T& value,
           std::pmr::memory_resource* mr = std::pmr::get_default_resource());

    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;

    Vector& operator=(Vector&& other) noexcept;

    Vector(std::initializer_list<T> init, 
        std::pmr::memory_resource* mr  = std::pmr::get_default_resource());

    T& operator[](size_t pos);

    const T& operator[](size_t pos) const;

    ForwardVectorIterator Begin() const noexcept;

    ForwardVectorIterator End() const noexcept;

    T& Front() const;

    T& Back() const;

    T* Data() const noexcept;

    bool IsEmpty() const noexcept;

    size_t Size() const noexcept;

    size_t Capacity() const noexcept;

    void Reserve(size_t new_cap);

    void Clear() noexcept;

    void Insert(size_t pos, T value);

    void Erase(size_t begin_pos, size_t end_pos);

    void PushBack(T value);

    template <class... Args>
    void EmplaceBack(Args&&... args);

    void PopBack();

    void Resize(size_t count, const T& value);

    ~Vector();

private:
    T* arr_;
    size_t sz_;
    size_t cap_;
    std::pmr::polymorphic_allocator<T> allocator_;
};
}
#include "vector.ipp"