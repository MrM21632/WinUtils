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

/**
 *  @brief Integer Square Root
 *  
 *  @param [in] n Operand
 *  @return An integer equivalent to (uint64_t)floor(sqrt(n)).
 *  
 *  @details Computes the integer square root of a given integer.
 */
uint64_t isqrt(uint64_t);

/**
 *  @brief Modular Addition
 *  
 *  @param [in] a Summand
 *  @param [in] b Summand
 *  @param [in] n Modulus
 *  @return (a + b) mod n.
 *  
 *  @details Performs modular addition on two integers with a given modulus.
 *           This implementation is written so as to avoid integer overflow.
 */
uint64_t mod_add(uint64_t, uint64_t, uint64_t);

/**
 *  @brief Modular Multiplication
 *  
 *  @param [in] a Multiplicand
 *  @param [in] b Multiplier
 *  @param [in] n Modulus
 *  @return ab mod n.
 *  
 *  @details Performs modular multiplication on two integers with a given
 *           modulus. This implementation is written so as to avoid integer
 *           overflow.
 */
uint64_t mod_mult(uint64_t, uint64_t, uint64_t);

/**
 *  @brief Modular Exponentiation
 *  
 *  @param [in] a Base
 *  @param [in] b Exponent
 *  @param [in] n Modulus
 *  @return a^b mod n.
 *  
 *  @details Performs modular exponentiation on two integers with a given
 *           modulus. This implementation is written so as to avoid integer
 *           overflow.
 */
uint64_t mod_pow(uint64_t, uint64_t, uint64_t);

/**
 *  @brief Miller-Rabin Primality Test
 *  
 *  @param [in] n Number to test for primality; must be odd
 *  @param [in] d A divisor of n-1; must be odd
 *  @return Returns true if n is likely prime, or false otherwise.
 *  
 *  @details Performs a non-deterministic primality test on a given integer to
 *           determine if it is composite or (likely) prime.
 */
bool miller_rabin(uint64_t, uint64_t);

/**
 *  @brief Main Primality Test Algorithm
 *  
 *  @param [in] n Number to test for primality; must be odd
 *  @param [in] k Number of times to repeat the test
 *  @return Returns true if n is likely prime, or false otherwise.
 *  
 *  @details Performs a series of non-deterministic primality tests on a given
 *           integer to determine if it is composite or (likely) prime. If any
 *           test fails, we immediately assume compositeness.
 */
bool is_prime(uint64_t, uint64_t);

/**
 *  @brief Sieve of Atkin
 *  
 *  @param [in] n Upper bound for the sieve
 *  @return A list of "integers" marked for primality.
 *  
 *  @details Performs the sieve of Atkin, a variation of the sieve of
 *           Eratosthenes, to generate a list of all primes up to a given upper
 *           bound.
 */
bool *sieve_of_atkin(uint64_t);

#endif  // __GUARD__PRIME_UTILS_H
