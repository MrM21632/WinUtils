/*
 * factor_utils.h: Function and structure declarations for integer
 * factorization. The following methods are declared here:
 *     - Pollard's rho algorithm, which uses modular addition
 *     - Trial division, which uses the Sieve of Atkin
 *     - Binary GCD algorithm, which is used by Pollard's rho algorithm
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 2/6/2018, 1:20am
 */

#ifndef __GUARD__FACTOR_UTILS_H
#define __GUARD__FACTOR_UTILS_H

// We need prime_utils.h for some of the functions it has, so we must include it
// here. We're also including the map library for the purpose of having access
// to it in this header.
#include <map>
#include "prime_utils.h"

/* Function Declarations */

uint64_t gcd(uint64_t, uint64_t);
std::map<uint64_t, uint64_t> trial_division(uint64_t);
uint64_t pollard(uint64_t, uint64_t);

#endif  // __GUARD__FACTOR_UTILS_H
