// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <data/math/number/bounded.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock/gmock-matchers.h"
#include <stdexcept>
#include <iostream>

namespace data::math {
    
    TEST(BoundedTest, BitNegate) {
        
        EXPECT_EQ(~N_bytes_big{"0x00"}, N_bytes_big{"0xff"});
        EXPECT_EQ(~N_bytes_little{"0x00"}, N_bytes_little{"0xff"});
        EXPECT_EQ(~N_bytes_big{"0xff"}, N_bytes_big{"0x00"});
        EXPECT_EQ(~N_bytes_little{"0xff"}, N_bytes_little{"0x00"});
        EXPECT_EQ(~Z_bytes_big{"0x00"}, Z_bytes_big{"0xff"});
        EXPECT_EQ(~Z_bytes_little{"0x00"}, Z_bytes_little{"0xff"});
        EXPECT_EQ(~Z_bytes_big{"0xff"}, Z_bytes_big{"0x00"});
        EXPECT_EQ(~Z_bytes_little{"0xff"}, Z_bytes_little{"0x00"});
        
    }
    
    TEST(BoundedTest, BitShift) {
        
        using u12l = uint_little<12>;
        using u12b = uint_big<12>;
        using s12l = sint_little<12>;
        using s12b = sint_big<12>;
        
        using nl = N_bytes_little;
        using nb = N_bytes_big;
        using zl = Z_bytes_little;
        using zb = Z_bytes_big;
        
        std::string     base_value{"0x100000000001000000000001"};
        std::string  shift_1_right{"0x080000000000800000000000"};
        std::string   shift_1_left{"0x200000000002000000000002"};
        std::string  shift_2_right{"0x040000000000400000000000"};
        std::string   shift_2_left{"0x400000000004000000000004"};
        std::string  shift_4_right{"0x010000000000100000000000"};
        std::string   shift_4_left{"0x000000000010000000000010"};
        std::string shift_33_right{"0x000000000800000000008000"};
        std::string  shift_33_left{"0x000200000000000200000000"};
        std::string shift_66_right{"0x000000000000000004000000"};
        std::string  shift_66_left{"0x000000040000000000000000"};
        
        EXPECT_EQ(u12l{base_value} << 1, u12l{shift_1_right});
        EXPECT_EQ(u12b{base_value} << 1, u12b{shift_1_right});
        EXPECT_EQ(s12l{base_value} << 1, s12l{shift_1_right});
        EXPECT_EQ(s12b{base_value} << 1, s12b{shift_1_right});
        
        EXPECT_EQ(nl{base_value} << 1, nl{shift_1_right});
        EXPECT_EQ(nb{base_value} << 1, nb{shift_1_right});
        EXPECT_EQ(zl{base_value} << 1, zl{shift_1_right});
        EXPECT_EQ(zb{base_value} << 1, zb{shift_1_right});
        
        EXPECT_EQ(u12l{base_value} << 2, u12l{shift_2_right});
        EXPECT_EQ(u12b{base_value} << 2, u12b{shift_2_right});
        EXPECT_EQ(s12l{base_value} << 2, s12l{shift_2_right});
        EXPECT_EQ(s12b{base_value} << 2, s12b{shift_2_right});
        
        EXPECT_EQ(nl{base_value} << 2, nl{shift_2_right});
        EXPECT_EQ(nb{base_value} << 2, nb{shift_2_right});
        EXPECT_EQ(zl{base_value} << 2, zl{shift_2_right});
        EXPECT_EQ(zb{base_value} << 2, zb{shift_2_right});
        
        EXPECT_EQ(u12l{base_value} << 4, u12l{shift_4_right});
        EXPECT_EQ(u12b{base_value} << 4, u12b{shift_4_right});
        EXPECT_EQ(s12l{base_value} << 4, s12l{shift_4_right});
        EXPECT_EQ(s12b{base_value} << 4, s12b{shift_4_right});
        
        EXPECT_EQ(nl{base_value} << 4, nl{shift_4_right});
        EXPECT_EQ(nb{base_value} << 4, nb{shift_4_right});
        EXPECT_EQ(zl{base_value} << 4, zl{shift_4_right});
        EXPECT_EQ(zb{base_value} << 4, zb{shift_4_right});
        
        EXPECT_EQ(u12l{base_value} << 33, u12l{shift_33_right});
        EXPECT_EQ(u12b{base_value} << 33, u12b{shift_33_right});
        EXPECT_EQ(s12l{base_value} << 33, s12l{shift_33_right});
        EXPECT_EQ(s12b{base_value} << 33, s12b{shift_33_right});
        
        EXPECT_EQ(nl{base_value} << 33, nl{shift_33_right});
        EXPECT_EQ(nb{base_value} << 33, nb{shift_33_right});
        EXPECT_EQ(zl{base_value} << 33, zl{shift_33_right});
        EXPECT_EQ(zb{base_value} << 33, zb{shift_33_right});
        
        EXPECT_EQ(u12l{base_value} << 66, u12l{shift_66_right});
        EXPECT_EQ(u12b{base_value} << 66, u12b{shift_66_right});
        EXPECT_EQ(s12l{base_value} << 66, s12l{shift_66_right});
        EXPECT_EQ(s12b{base_value} << 66, s12b{shift_66_right});
        
        EXPECT_EQ(nl{base_value} << 66, nl{shift_66_right});
        EXPECT_EQ(nb{base_value} << 66, nb{shift_66_right});
        EXPECT_EQ(zl{base_value} << 66, zl{shift_66_right});
        EXPECT_EQ(zb{base_value} << 66, zb{shift_66_right});
        
        EXPECT_EQ(u12l{base_value} >> 1, u12l{shift_1_left});
        EXPECT_EQ(u12b{base_value} >> 1, u12b{shift_1_left});
        EXPECT_EQ(s12l{base_value} >> 1, s12l{shift_1_left});
        EXPECT_EQ(s12b{base_value} >> 1, s12b{shift_1_left});
        
        EXPECT_EQ(nl{base_value} >> 1, nl{shift_1_left});
        EXPECT_EQ(nb{base_value} >> 1, nb{shift_1_left});
        EXPECT_EQ(zl{base_value} >> 1, zl{shift_1_left});
        EXPECT_EQ(zb{base_value} >> 1, zb{shift_1_left});
        
        EXPECT_EQ(u12l{base_value} >> 2, u12l{shift_2_left});
        EXPECT_EQ(u12b{base_value} >> 2, u12b{shift_2_left});
        EXPECT_EQ(s12l{base_value} >> 2, s12l{shift_2_left});
        EXPECT_EQ(s12b{base_value} << 2, s12b{shift_2_left});
        
        EXPECT_EQ(nl{base_value} >> 2, nl{shift_2_left});
        EXPECT_EQ(nb{base_value} >> 2, nb{shift_2_left});
        EXPECT_EQ(zl{base_value} >> 2, zl{shift_2_left});
        EXPECT_EQ(zb{base_value} >> 2, zb{shift_2_left});
        
        EXPECT_EQ(u12l{base_value} >> 4, u12l{shift_4_left});
        EXPECT_EQ(u12b{base_value} >> 4, u12b{shift_4_left});
        EXPECT_EQ(s12l{base_value} >> 4, s12l{shift_4_left});
        EXPECT_EQ(s12b{base_value} >> 4, s12b{shift_4_left});
        
        EXPECT_EQ(nl{base_value} >> 4, nl{shift_4_left});
        EXPECT_EQ(nb{base_value} >> 4, nb{shift_4_left});
        EXPECT_EQ(zl{base_value} >> 4, zl{shift_4_left});
        EXPECT_EQ(zb{base_value} >> 4, zb{shift_4_left});
        
        EXPECT_EQ(u12l{base_value} >> 33, u12l{shift_33_left});
        EXPECT_EQ(u12b{base_value} >> 33, u12b{shift_33_left});
        EXPECT_EQ(s12l{base_value} >> 33, s12l{shift_33_left});
        EXPECT_EQ(s12b{base_value} >> 33, s12b{shift_33_left});
        
        EXPECT_EQ(nl{base_value} >> 33, nl{shift_33_left});
        EXPECT_EQ(nb{base_value} >> 33, nb{shift_33_left});
        EXPECT_EQ(zl{base_value} >> 33, zl{shift_33_left});
        EXPECT_EQ(zb{base_value} >> 33, zb{shift_33_left});
        
        EXPECT_EQ(u12l{base_value} >> 66, u12l{shift_66_left});
        EXPECT_EQ(u12b{base_value} >> 66, u12b{shift_66_left});
        EXPECT_EQ(s12l{base_value} >> 66, s12l{shift_66_left});
        EXPECT_EQ(s12b{base_value} >> 66, s12b{shift_66_left});
        
        EXPECT_EQ(nl{base_value} >> 66, nl{shift_66_left});
        EXPECT_EQ(nb{base_value} >> 66, nb{shift_66_left});
        EXPECT_EQ(zl{base_value} >> 66, zl{shift_66_left});
        EXPECT_EQ(zb{base_value} >> 66, zb{shift_66_left});
        
    }
    
}

