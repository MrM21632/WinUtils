/*
 * factor_utils.h: Function and structure declarations for integer factorization.
 * The following methods are declared here:
 *     - Pollard's rho algorithm, with Floyd's cycle-detection algorithm
 *     - Trial division, which uses the Sieve of Atkin
 *     - Greatest Common Divisor, which is used by Pollard's rho algorithm
 * Methods for the Dynamic Array are also declared here.
 *
 * Version:     1.2.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/4/2017, 8:00pm
 */

#ifndef __GUARD__FACTOR_UTILS_H_
#define __GUARD__FACTOR_UTILS_H_

// We need prime_utils.h for some of the functions it has, so we must include it
// here. We're also including vector for the purpose of having access to it in
// this header.
#include <map>
#include "prime_utils.h"

/* Function Declarations */
extern uint64_t gcd(uint64_t, uint64_t);
extern std::map<uint64_t, uint64_t> trial_div(uint64_t);
extern uint64_t pollard(uint64_t, uint64_t);

#endif  // __GUARD__FACTOR_UTILS_H_