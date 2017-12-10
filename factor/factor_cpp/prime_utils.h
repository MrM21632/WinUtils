/*
 * prime_utils.h: Function and type declarations for working with primes. The
 * following methods are declared here:
 *     - Miller-Rabin probabilistic primality test, with an iterative tester
 *       method
 *     - Modular addition, which is used by modular multiplication
 *     - Modular multiplication and exponentiation, which are used by the
 *       Miller-Rabin test
 *     - Sieve of Atkin
 *     - Integer square root, which is used by the Sieve
 *
 * Version:     1.3.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/10/2017, 9:25am
 */

#ifndef __GUARD__PRIME_UTILS_H_
#define __GUARD__PRIME_UTILS_H_

// In order to use uint64_t, we need to include cstdint.
#include <cstdint>

/* Function Declarations */
extern uint64_t isqrt(uint64_t);
extern uint64_t mod_add(uint64_t, uint64_t, uint64_t);
extern uint64_t mod_mult(uint64_t, uint64_t, uint64_t);
extern uint64_t mod_pow(uint64_t, uint64_t, uint64_t);
extern bool miller_rabin(uint64_t, uint64_t);
extern bool is_prime(uint64_t, uint64_t);
extern bool* sieve_atkin(uint64_t);

#endif  // __GUARD__PRIME_UTILS_H_