// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <data/math/number/gmp/N.hpp>
#include <data/math/number/bytes/Z.hpp>
#include <data/encoding/integer.hpp>

namespace data::math::number::gmp {
    
    Z::Z(const N& n) : Z{n.valid() ? n.Value : Z{}} {}
    
    Z Z_read_N_gmp(string_view s) {
        Z z{};
        mpz_init(z.MPZ);
        mpz_set_str(z.MPZ, std::string{s}.c_str(), 0);
        return z;
    }
    
    Z Z_read_N_data(string_view x) {
        if (encoding::decimal::valid(x)) {
            string s{x};
            return Z_read_N_gmp(s);
        } 
        
        if (encoding::hexidecimal::valid(x)) {
            if (encoding::hexidecimal::zero(x)) return Z{0};
            int first_nonzero_index = 2;
            while (true) {
                if (first_nonzero_index == x.size()) return Z{0};
                if (x[first_nonzero_index] != '0') break;
                first_nonzero_index++;
            }
            std::stringstream ss;
            ss << "0x";
            ss << x.substr(first_nonzero_index);
            return Z_read_N_gmp(ss.str());
        }
        
        return Z{}; // shouldn't really happen;
    }
    
    Z Z_read_hex_positive(string_view x) {
        int first_nonzero_index = 2;
        while (true) {
            if (first_nonzero_index == x.size()) return Z{0};
            if (x[first_nonzero_index] != '0') break;
            first_nonzero_index++;
        }
        std::stringstream ss;
        ss << "0x";
        ss << x.substr(first_nonzero_index); 
        return Z_read_N_gmp(ss.str());
    }
    
    Z Z_read_hex(string_view x) {
        //std::cout << "  reading in Z with hexidecimal representation " << x << std::endl;
        if (encoding::hexidecimal::zero(x)) return Z{0};
        //std::cout << "  representation is nonzero. " << std::endl;
        if (encoding::integer::negative(x)) {
        //std::cout << "  representation is negative. " << std::endl;
            std::stringstream ss;
            ss << "0x01";
            for (int i = 0; i < x.size() - 2; i += 2) ss << "00";
            //std::cout << "  returning " << Z{N{x}} << " minus " << std::endl;
            return Z{N{x}} - Z_read_hex_positive(ss.str());
        };
        return Z_read_hex_positive(x);
    }
    
    Z Z::read(string_view s) {
        //std::cout << "  reading in Z with representation " << s << std::endl;
        if (!encoding::integer::valid(s)) return Z{};
        //std::cout << "  representation is valid " << s << std::endl;
        if (encoding::hexidecimal::valid(s)) return Z_read_hex(s);
        return encoding::integer::negative(s) ? -Z_read_N_gmp(s.substr(1)) : Z_read_N_gmp(s);
    }
    
    void Z_write_dec(std::ostream& o, const Z& n) {
        o << std::dec << n.MPZ;
    }
    
    void Z_write_hex(std::ostream& o, const Z& n) {
        std::stringstream gmp_format_stream;
        gmp_format_stream << std::hex << n.MPZ;
        std::string gmp_format = gmp_format_stream.str();
        
        bool negative = n < 0;
        if (negative) o << "-";
        
        o << "0x";
        if (gmp_format.size() % 2 == (negative ? 0 : 1)) o << "0";
        o << (negative ? string_view{gmp_format}.substr(1) : gmp_format);
    }
    
}

namespace data::encoding::hexidecimal {
    
    std::string write(const math::number::gmp::Z& n) {
        std::stringstream ss;
        ss << std::hex << n;
        return ss.str();
    }
    
}

namespace data::encoding::integer {
    
    std::string write(const math::number::gmp::Z& n) {
        std::stringstream ss;
        ss << std::dec << n;
        return ss.str();
    }
    
}

std::ostream& operator<<(std::ostream& o, const data::math::number::gmp::Z& n) {
    if (o.flags() & std::ios::hex) {
        data::math::number::gmp::Z_write_hex(o, n);
        return o;
    }
    if (o.flags() & std::ios::dec) {
        data::math::number::gmp::Z_write_dec(o, n);
        return o;
    }
    o << &n.MPZ;
    return o;
}

namespace data::math::number::gmp {
    
    Z N_read_hex(string_view x) {
        if (encoding::hexidecimal::zero(x)) return N{0};
        return Z_read_hex_positive(x);
    }
    
    Z N_read(string_view x) {
        if (!encoding::integer::valid(x)) return Z{};
        if (encoding::hexidecimal::valid(x)) return N_read_hex(x);
        if (encoding::integer::negative(x)) return Z{};
        return Z_read_N_gmp(x);
    }
    
    N::N(string_view x) : Value{N_read(x)} {}
    
    void N_write_dec(std::ostream& o, const N& n) {
        o << std::dec << n.Value.MPZ;
    }
    
    void N_write_hex(std::ostream& o, const N& n) {
        std::stringstream gmp_format_stream;
        gmp_format_stream << std::hex << n.Value.MPZ;
        std::string gmp_format = gmp_format_stream.str();
        
        o << "0x";
        if (gmp_format.size() % 2 == 1) o << "0";
        o << gmp_format;
    }
    
    // inefficient but easier to write and more certain to be correct. 
    N read_bytes_big(bytes_view x) {
        std::stringstream format_stream;
        format_stream << "0x" << encoding::hex::write(x);
        return N{format_stream.str()};
    }
    
    N read_bytes_little(bytes_view x) {
        auto z = std::basic_string<byte>{x};
        std::reverse(z.begin(), z.end());
        return read_bytes_big(z);
    }
    
    N read_bytes(bytes_view x, endian::order o) {
        if (o == endian::order::big) return read_bytes_big(x);
        return read_bytes_little(x);
        /* 
        N r{0};
        if (x.size() > 0) { 
            if (o == endian::order::little) {
                r += x[0];
                for (int i = 1; i < x.size(); i++) {
                    r <<= 8;
                    r += x[i];
                }
            } else {
                r += x[x.size() - 1];
                for (int i = x.size() - 2; i >= 0; i--) {
                    r <<= 0;
                    r += x[i];
                }
            }
        }
        return r;*/
    }
    
    N::N(bytes_view x, endian::order o) : Value{read_bytes(x, o).Value} {}
    
    void N_write_big(bytes& b, const N& n) {
        b = bytes(data::encoding::hex::string{data::encoding::hexidecimal::write(n).substr(2)});
    }
    
    void N_write_little(bytes& b, const N& n) {
        N_write_big(b, n);
        std::reverse(b.begin(), b.end());
    }
        
    void N::write_bytes(bytes& b, endian::order o) const {
        if (o == endian::order::big) {
            N_write_big(b, *this);
            return;
        }
        
        N_write_little(b, *this);
        
        /* I didn't finish this because it was getting too confusing. But it's more efficient. 
        int last = Value.size() - 1;
        while(last >= 0 && Value[last] == 0) last--;
        if (last == -1) return bytes{};
        gmp_uint big_endian = endian::native<gmp_uint, endian::big>::from(Value[last]);
        int extra = 0;
        while (((byte*)(&big_endian))[extra] == 0) extra++;
        size_t size = sizeof(gmp_uint) * (last + 1) - extra;
        bytes b{size, ' '};
        */
    }
    
}

std::ostream& operator<<(std::ostream& o, const data::math::number::gmp::N& n) {
    if (o.flags() & std::ios::hex) {
        data::math::number::gmp::N_write_hex(o, n);
        return o;
    }
    if (o.flags() & std::ios::dec) {
        data::math::number::gmp::N_write_dec(o, n);
        return o;
    }
    o << &n.Value.MPZ;
    return o;
}

namespace data::encoding::hexidecimal { 
    
    std::string write(const math::number::gmp::N& n) {
        std::stringstream ss;
        ss << std::hex << n;
        return ss.str();
    }
    
}

namespace data::encoding::integer {
    
    std::string write(const math::number::gmp::N& n) {
        std::stringstream ss;
        ss << std::dec << n;
        return ss.str();
    }
    
}
