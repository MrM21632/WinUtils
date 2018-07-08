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

/**
 *  @brief Binary GCD Algorithm
 *  
 *  @param [in] a Operand
 *  @param [in] b Operand
 *  @return gcd(a, b).
 *  
 *  @details Computes the greatest common divisor (GCD) of two integers. This is
 *           specifically the binary GCD algorithm, a variation of the standard
 *           algorithm that heavily makes use of shift operations.
 */
uint64_t gcd(uint64_t, uint64_t);

/**
 *  @brief Trial Division
 *  
 *  @param [in] n The number to factorize
 *  @return A collection of the factors of n. Each entry is a pair of the format
 *          (f, m), where f is a factor of n and m is the number of times f is
 *          factored out of n.
 *  
 *  @details Performs trial division on a given integer, computing and collecting
 *           its factors. This is the simplest factorization algorithm, and
 *           consequently is best used for smaller numbers and/or those with
 *           especially simple prime decompositions, as it is used here. This
 *           implementation uses the sieve of Atkin to simplify some operations
 *           and loops.
 */
std::map<uint64_t, uint64_t> trial_division(uint64_t);

/**
 *  @brief Pollard's Rho Algorithm
 *  
 *  @param [in] n The number being factorized
 *  @param [in] c Constant summand used in the function
 *  @return A non-trivial factor of n.
 *  
 *  @details Performs Pollard's rho algorithm to compute a single, non-trivial
 *           (i.e., not 1 or the number itself) factor of a given integer. This
 *           implementation uses Floyd's cycle-detection algorithm.
 */
uint64_t pollard(uint64_t, uint64_t);

#endif  // __GUARD__FACTOR_UTILS_H
