// Copyright (c) 2019-2022 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "data/numbers.hpp"
#include "data/math/number/extended_euclidian.hpp"
#include "gtest/gtest.h"

namespace data {
    
    using Nb = N_bytes_big;
    using Nl = N_bytes_little;
    
    using Zb1 = Z_bytes_big;
    using Zl1 = Z_bytes_little;
    
    template <typename Z, typename N>
    struct test_extended_euclidian {
        test_extended_euclidian() {
            using X = math::number::euclidian::extended<Z, N>;
            EXPECT_THROW(X::algorithm(N{0}, N{0}).GCD, math::division_by_zero);
            
            EXPECT_EQ(X::algorithm(N{1}, N{1}).GCD, 1);
            
            EXPECT_EQ(X::algorithm(N{2}, N{4}).GCD, 2);
            
            EXPECT_EQ(X::algorithm(N{1145}, N{916}).GCD, 229);
        }
    };
    
    TEST(ExtendedEuclinianTest, TestExtendedEuclidian) {
        test_extended_euclidian<int64, int64> {};
        test_extended_euclidian<Z, N>{};
        test_extended_euclidian<Zl1, Nl>{};
        test_extended_euclidian<Zb1, Nb>{};
        test_extended_euclidian<int_big<9>, uint_big<9>>{};
        test_extended_euclidian<int_big<10>, uint_big<10>>{};
        test_extended_euclidian<int_big<11>, uint_big<11>>{};
        test_extended_euclidian<int_big<20>, uint_big<20>>{};
        test_extended_euclidian<dec_int, dec_uint>{};
        
    }
    
}
