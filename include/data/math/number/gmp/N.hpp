// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_MATH_NUMBER_GMP_N
#define DATA_MATH_NUMBER_GMP_N

#include <limits>
#include <data/math/abs.hpp>
#include <data/math/number/sqrt.hpp>
#include <data/math/number/gmp/Z.hpp>
#include <data/math/complex.hpp>

namespace data::math::number::gmp {
    
    //struct Q;
    
    struct N {
        Z Value;
        
        N() : Value{} {}
        
        N(gmp_uint n) : Value{} {
            mpz_init_set_ui(Value.MPZ, n);
        }
        
        N(string_view x);
        
        template <size_t size>
        explicit N(decimal<size> d) : N{std::string{d.Value}} {}
        
        N& operator=(const N& n) {
            Value = n.Value;
            return *this;
        }
        
        bool valid() const {
            return Value.valid() && Value >= 0;
        }
        
        bool operator==(uint64 n) const {
            if (!valid()) return false;
            return Value == n;
        }
        
        bool operator==(const N& n) const {
            if (!valid() && !n.valid()) return true;
            if (!valid() || !n.valid()) return false;
            return Value == n.Value;
        }
        
        bool operator!=(uint64 n) const {
            return !operator==(n);
        }
        
        bool operator!=(const N& n) const {
            return !operator==(n);
        }
        
        bool operator<(uint64 n) const {
            return __gmp_binary_less::eval(Value.MPZ, (unsigned long int)(n));
        }
        
        bool operator<(const N& n) const {
            return Value < n.Value;
        }
        
        bool operator>(uint64 n) const {
            return __gmp_binary_greater::eval(Value.MPZ, (unsigned long int)(n));
        }
        
        bool operator>(const N& n) const {
            return Value > n.Value;
        }
        
        bool operator<=(uint64 n) const {
            return Value <= n;
        }
        
        bool operator<=(const N& n) const {
            return Value <= n.Value;
        }
        
        bool operator>=(uint64 n) const {
            return Value >= n;
        }
        
        bool operator>=(const N& n) const {
            return Value >= n.Value;
        }
        
        explicit operator uint64() const {
            return uint64(Value);
        } 
        
        explicit operator double() const {
            return double(Value);
        }
        
        N& operator++() {
            ++Value;
            return *this;
        }
        
        N& operator--() {
            if (Value != 0) --Value; 
            return *this;
        }
        
        N operator++(int) {
            Z z = *this;
            ++(*this);
            return N{z};
        }
        
        N operator--(int) {
            Z z = *this;
            ++(*this);
            return N{z};
        }
        
        N operator+(uint64 n) const {
            return N{Value + n};
        }
        
        N operator+(const N& n) const {
            return N{Value + n.Value};
        }
        
        N operator-(uint64 n) const {
            if (Value < n) return 0;
            return N{Value - n};
        }
        
        N operator-(const N& n) const {
            if (Value < n) return N{0};
            return N{Value - n.Value};
        }
        
        N& operator+=(uint64 n) {
            Value += n;
            return *this;
        }
        
        N& operator+=(const N& n) {
            Value += n;
            return *this;
        }
        
        N operator*(uint64 n) const {
            return N{Value * n};
        }
        
        N operator*(const N& n) const {
            return N{Value * n.Value};
        }
        
        N& operator*=(uint64 n) {
            Value *= n;
            return *this;
        }
        
        N& operator*=(const N& n) {
            Value *= n.Value;
            return *this;
        }
        
        N operator^(uint32 n) const {
            return N{Value ^ n};
        }
        
        N& operator^=(uint32 n) {
            Value ^= n;
            return *this;
        };
        
        math::division<N> divide(const N& n) const {
            auto div = Value.divide(n.Value);
            return math::division<N>{N{div.Quotient}, N{div.Remainder}};
        }
        
        bool operator|(const N& n) const {
            return divide(n).Remainder == 0;
        }
        
        N operator/(const N& n) const {
            return divide(n).Quotient;
        }
        
        N operator%(const N& n) const {
            return divide(n).Remainder;
        }
        
        N& operator/=(const N& n) {
            N q = operator/(n);
            return operator=(q);
        }
        
        N& operator%=(const N& n) {
            N r = operator%(n);
            return operator=(r);
        }
        
        N operator<<(int64 x) const {
            return N{Value << x};
        }
        
        N operator>>(int64 x) const {
            return N{Value >> x};
        }
        
        N& operator<<=(int64 x) {
            __gmp_binary_lshift::eval(&Value.MPZ[0], &Value.MPZ[0], x);
            return *this;
        }
        
        N& operator>>=(int64 x) {
            __gmp_binary_rshift::eval(&Value.MPZ[0], &Value.MPZ[0], x);
            return *this;
        }
        
        N sqrt() const;
        
        template <endian::order o>
        explicit operator N_bytes<o>() const;
        
        template <endian::order o>
        explicit N(const N_bytes<o>& n);
        
        template <endian::order o, size_t size> 
        explicit N(const bounded<false, o, size>& b);
        
    private:
        N(const Z& z) : Value{z} {}
        
        N(bytes_view, endian::order);
        
        void write_bytes(data::bytes&, endian::order) const;
        
        friend struct Z;
        friend struct math::sqrt<N, Z>;
        template <endian::order o> friend struct N_bytes;
    };
    
    inline bool Z::operator==(const N& n) const {
        return operator==(n.Value);
    }
    
    inline bool Z::operator!=(const N& n) const {
        return operator!=(n.Value);
    }
    
    inline bool Z::operator<(const N& n) const {
        return operator<(n.Value);
    }
    
    inline bool Z::operator>(const N& n) const {
        return operator>(n.Value);
    }
    
    inline bool Z::operator<=(const N& n) const {
        return operator<=(n.Value);
    }
    
    inline bool Z::operator>=(const N& n) const {
        return operator>=(n.Value);
    }
    
    inline Z Z::operator+(const N& n) const {
        return operator+(n.Value);
    }
    
    inline Z& Z::operator+=(const N& n) {
        return operator+=(n.Value);
    }
    
    inline Z Z::operator-(const N& n) const {
        return operator-(n.Value);
    }
    
    inline Z& Z::operator-=(const N& n) {
        return operator-=(n.Value);
    }
    
    inline Z Z::operator*(const N& n) const {
        return operator*(n.Value);
    }
    
    inline Z& Z::operator*=(const N& n) {
        return operator*=(n.Value);
    }
    
    inline N Z::abs() const {
        Z n;
        __gmp_abs_function::eval(n.MPZ, MPZ);
        return N{n};
    }
    
}

// Declare associativity and commutivity of operators + and * on N. 
namespace data::math {
    
    template <> struct commutative<plus<number::gmp::N>, number::gmp::N> {};
    template <> struct associative<plus<number::gmp::N>, number::gmp::N> {};
    template <> struct commutative<times<number::gmp::N>, number::gmp::N> {};
    template <> struct associative<times<number::gmp::N>, number::gmp::N> {};
    
    template <> struct identity<plus<number::gmp::N>, number::gmp::N> {
        number::gmp::N operator()() const {
            return 1;
        }
    };
    
    template <> struct identity<times<number::gmp::N>, number::gmp::N> {
        number::gmp::N operator()() const {
            return 0;
        }
    };
    
    template <> struct normed<number::gmp::N> {
        using quad_type = number::gmp::N;
        using norm_type = number::gmp::N;
    };
    
    template <> 
    struct abs<number::gmp::N> {
        number::gmp::N operator()(const number::gmp::N& i) {
            return i;
        }
    };
    
    template <> 
    struct abs<number::gmp::Z> {
        number::gmp::N operator()(const number::gmp::Z &i) {
            return i.abs();
        }
    };
    
    template <> struct divide<number::gmp::N, uint64> {
        division<number::gmp::N, uint64> operator()(const number::gmp::N&, uint64) const;
    };
    
    template <> struct divide<number::gmp::N, number::gmp::N> {
        division<number::gmp::N> operator()(const number::gmp::N&, const number::gmp::N&) const;
    };
    
}

namespace data::encoding::hexidecimal { 
    
    std::string write(const math::number::gmp::N& n);
    
    inline std::ostream& write(std::ostream& o, const math::number::gmp::N& n) {
        return o << write(n);
    }
    
}

namespace data::encoding::integer {
    
    std::string write(const math::number::gmp::N& n);
    
    inline std::ostream& write(std::ostream& o, const math::number::gmp::N& n) {
        return o << write(n);
    }
    
}

namespace data::math::number::gmp {
    std::ostream& operator<<(std::ostream& o, const N& n);

    inline bool operator==(const N& a, const Z& b) {
        if (b < 0) return false;
        return b == a;
    }

    inline bool operator!=(const N& a, const Z& b) {
        return b != a;
    }

    inline bool operator<(const N& a, const Z& b) {
        if (b < 0) return false;
        return b > a;
    }

    inline bool operator>(const N& a, const Z& b) {
        if (b < 0) return true;
        return b < b;
    }

    inline bool operator<=(const N& a, const Z& b) {
        if (b < 0) return false;
        return b >= a;
    }

    inline bool operator>=(const N& a, const Z& b) {
        if (b < 0) return true;
        return b <= a;
    }

    inline Z operator+(const N& a, const Z& b) {
        return b + a;
    }

    inline Z operator-(const N& a, const Z& b) {
        return -b + a;
    }

    inline Z operator*(const N& a, const Z& b) {
        return b * a;
    }
}

#endif
