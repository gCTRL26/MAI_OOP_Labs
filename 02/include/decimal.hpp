#pragma once

#include "vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <string>

// signature for decimal

namespace decimal {
    class Decimal {
      private:
        vector::Vector arr_;

      public:
        Decimal();

        Decimal(const size_t& n, unsigned char t = 0);

        Decimal(const std::initializer_list<unsigned char>& t);

        Decimal(const std::string& t);

        Decimal(const Decimal& other);

        Decimal(Decimal&& other) noexcept;

        ~Decimal() noexcept;

        static Decimal Add(const Decimal& other1, const Decimal& other2);

        static Decimal Sub(const Decimal& other1, const Decimal& other2);

        static Decimal Prod(const Decimal& other1, const Decimal& other2);

        std::string ShowNumber() const;

        void Copy(const Decimal& other);

        bool GreaterThen(const Decimal& other) const;

        bool LessThen(const Decimal& other) const;

        bool Equal(const Decimal& other) const;
    };
}