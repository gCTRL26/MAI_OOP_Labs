#include "../include/decimal.hpp"
#include "../include/exception.hpp"

namespace decimal {

    Decimal::Decimal(): arr_(vector::Vector(1, 0)) {}

    Decimal::Decimal(const size_t& n, unsigned char t): arr_(vector::Vector(n, t)) {}

    Decimal::Decimal(const std::initializer_list<unsigned char>& t): arr_(vector::Vector(t.size(), 0)) {
        size_t i = t.size() - 1;
        for (unsigned char c: t) {
            arr_.Get(i) = c;
            --i;
        }

        while (arr_.Size() > 1 && arr_.Back() == 0) {
            arr_.PopBack();
        } 
    }

    Decimal::Decimal(const std::string& t): arr_(vector::Vector()) {
        if (t.empty()) {
            arr_.PushBack(0);
            return; 
        }
        
        for (int64_t i = t.size() - 1; i >= 0; --i) {
            char c = t[i];
            if (c > '9' || c < '0') {
                throw exception::NaNException("Not a number");
            }
            arr_.PushBack(c - '0');
        }
        while (arr_.Size() > 1 && arr_.Back() == 0) {
            arr_.PopBack();
        } 
    }

    Decimal::Decimal(const Decimal& other): arr_(other.arr_) {}

    Decimal::Decimal(Decimal&& other) noexcept: arr_(std::move(other.arr_)) {}

    Decimal::~Decimal() noexcept {
        arr_.Clear();
    }

    Decimal Decimal::Add(const Decimal& other1, const Decimal& other2) {
        Decimal res;
        res.arr_.Clear();
        unsigned char carry = 0;
        size_t max_size = std::max(other1.arr_.Size(), other2.arr_.Size());
        
        for (size_t i = 0; i < max_size || carry != 0; ++i) {
            unsigned char sum = carry;
            if (i < other1.arr_.Size()) {
                sum += other1.arr_.Get(i);
            }
            if (i < other2.arr_.Size()) {
                sum += other2.arr_.Get(i);
            }
            res.arr_.PushBack(sum % 10);
            carry = sum / 10;
        }

        while (res.arr_.Size() > 1 && res.arr_.Back() == 0) {
            res.arr_.PopBack();
        } 
        return res;
    }

    Decimal Decimal::Sub(const Decimal& other1, const Decimal& other2) {
        if (other1.LessThen(other2)) {
            throw exception::NegativeException("Answer should be positive");
        } 
        
        if (other1.Equal(other2)) {
            return Decimal();
        }
        Decimal res = Decimal(other1.arr_.Size(), 0);
        int borrow = 0;
        for (size_t i = 0; i < other1.arr_.Size(); ++i) {
            int a = other1.arr_.Get(i);
            int b = (i < other2.arr_.Size()) ? other2.arr_.Get(i) : 0;
            
            // Вычитаем с учетом предыдущего заема
            a -= borrow;
            
            if (a < b) {
                res.arr_.Get(i) = a + 10 - b;
                borrow = 1;
            } else {
                res.arr_.Get(i) = a - b;
                borrow = 0;
            }
        }
    
        while (res.arr_.Size() > 1 && res.arr_.Back() == 0) {
            res.arr_.PopBack();
        } 
        return res;
    }

    Decimal Decimal::Prod(const Decimal& a, const Decimal& b) {
        if (a.arr_.Size() == 1 && a.arr_.Get(0) == 0) return Decimal();
        if (b.arr_.Size() == 1 && b.arr_.Get(0) == 0) return Decimal();

        Decimal res = Decimal(a.arr_.Size() + b.arr_.Size(), 0);

        for (size_t i = 0; i != a.arr_.Size(); ++i) {
            for (size_t j = 0; j != b.arr_.Size(); ++j) {
                res.arr_.Get(i + j) += a.arr_.Get(i) * b.arr_.Get(j); 
            }
        }

        unsigned char carry = 0;
        for (size_t i = 0; i != res.arr_.Size(); ++i) {
            unsigned char tot = res.arr_.Get(i) + carry;
            res.arr_.Get(i) = tot % 10;
            carry = tot / 10;
        }

        while (res.arr_.Size() > 1 && res.arr_.Back() == 0) {
            res.arr_.PopBack();
        } 
        return res;
    }

    std::string Decimal::ShowNumber() const {
        if (arr_.Size() == 0) {
            return "0";
        }
        std::string num;
        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            num += (arr_.Get(i) + '0');
        }
        return num;
    }

    void Decimal::Copy(const Decimal& other) {
        arr_.Copy(other.arr_);
    }

    bool Decimal::GreaterThen(const Decimal& other) const {
        if (arr_.Size() > other.arr_.Size()) {
            return true;
        } else if (arr_.Size() < other.arr_.Size()) {
            return false;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) > other.arr_.Get(i)) {
                return true;
            }
        }
        return false;
    }

    bool Decimal::LessThen(const Decimal& other) const {
        if (arr_.Size() < other.arr_.Size()) {
            return true;
        } else if (arr_.Size() > other.arr_.Size()) {
            return false;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) < other.arr_.Get(i)) {
                return true;
            }
        }
        return false;
    }

    bool Decimal::Equal(const Decimal& other) const {
        if (arr_.Size() != other.arr_.Size()) {
            return false;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) != other.arr_.Get(i)) {
                return false;
            }
        }
        return true;
    }
}