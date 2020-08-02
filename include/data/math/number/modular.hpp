// Copyright (c) 2019-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_MATH_NUMBER_MODULAR
#define DATA_MATH_NUMBER_MODULAR

#include <data/types.hpp>
#include <data/math/number/natural.hpp>

namespace data::math::number {
    
    template <typename X, auto & mod>
    struct modular {
        X Value;
        static X modulus() { 
            static X Mod(mod);
            return Mod;
        }
        
        modular() : Value{} {}
        modular(X x) : Value{x} {}
        
        bool valid() const {
            return Value < modulus();
        }
        
        bool operator==(const modular& m) const {
            return Value == m.Value;
        }
        
        bool operator!=(const modular& m) const {
            return Value != m.Value;
        }
        
        bool operator<(const modular& m) const {
            return Value < m.Value;
        }
        
        bool operator>(const modular& m) const {
            return Value > m.Value;
        }
        
        bool operator<=(const modular& m) const {
            return Value <= m.Value;
        }
        
        bool operator>=(const modular& m) const {
            return Value >= m.Value;
        }
        
        modular operator+(const modular& m) const {
            return (Value + m.Value) % modulus();
        }
        
        modular operator*(const modular& m) const {
            return (Value * m.Value) % modulus();
        }
        
        modular operator-(const modular& m) const {
            if (Value < m.Value) return modulus() - ((m.Value - Value) % modulus());
            return Value - m.Value;
        }
        
        modular operator-() const {
            return {modulus() - Value};
        }
        
    };
    
}

template <typename X, auto & mod>
inline std::ostream& operator<<(std::ostream& o, 
    const data::math::number::modular<X, mod>& m) {
    return o << m.Value;
}

#endif

