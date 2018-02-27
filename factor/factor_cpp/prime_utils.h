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
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 2/6/2018, 1:20am
 */

#ifndef __GUARD__PRIME_UTILS_H
#define __GUARD__PRIME_UTILS_H

// In order to use uint64_t, we need to include the stdint library
#include <cstdint>

/* Function Declarations */

uint64_t isqrt(uint64_t);
uint64_t mod_add(uint64_t, uint64_t, uint64_t);
uint64_t mod_mult(uint64_t, uint64_t, uint64_t);
uint64_t mod_pow(uint64_t, uint64_t, uint64_t);
bool miller_rabin(uint64_t, uint64_t);
bool is_prime(uint64_t, uint64_t);
bool *sieve_of_atkin(uint64_t);

#endif  // __GUARD__PRIME_UTILS_H
