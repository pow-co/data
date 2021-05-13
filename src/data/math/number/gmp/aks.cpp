// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <rotella/akslib.h>
#include <data/math/number/gmp/aks.hpp>

namespace data::math::number::gmp {
    
    bool aks_is_prime(const gmp::Z z) {
        return ::aks(mpz_class(&z.MPZ[0]));
    }
    
}

