/*
 * prime_utils.h: Function and type declarations for working with primes. The
 * following methods are declared here:
 *     - Miller-Rabin Probabilistic Primality Test, with an iterative tester
 *       method
 *     - Modular Addition, which is used in the modular multiplication algorithm
 *     - Modular Multiplication and Exponentiation functions, which are used by
 *       the Miller-Rabin test
 *     - Sieve of Atkin
 *     - Integer Square Root, which is used by the Sieve
 *
 * Version:     1.2.0
 * License:     Public Domain
 * Author:      Joshua Morrison (jmorrison708@comcast.net)
 * Last Edited: 11/4/2017, 8:00pm
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
extern bool *sieve_atkin(uint64_t);

#endif  // __GUARD__PRIME_UTILS_H_