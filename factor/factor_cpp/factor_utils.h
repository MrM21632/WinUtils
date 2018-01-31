/*
 * factor_utils.h: Function and structure declarations for integer
 * factorization. The following methods are declared here:
 *     - Pollard's rho algorithm, which uses modular addition
 *     - Trial division, which uses the Sieve of Atkin
 *     - Binary GCD algorithm, which is used by Pollard's rho algorithm
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#ifndef __GUARD__FACTOR_UTILS_H_
#define __GUARD__FACTOR_UTILS_H_

// We need prime_utils.h for some of the functions it has, so we must include it
// here. We're also including the map library for the purpose of having access
// to it in this header.
#include <map>
#include "prime_utils.h"

/* Function Declarations */
extern uint64_t gcd(uint64_t, uint64_t);
extern std::map<uint64_t, uint64_t> trial_div(uint64_t);
extern uint64_t pollard(uint64_t, uint64_t);

#endif  // __GUARD__FACTOR_UTILS_H_