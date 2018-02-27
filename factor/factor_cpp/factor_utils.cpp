/*
 * factor_utils.cpp: Function definitions for integer factorization. The
 * following methods are defined here:
 *     - Pollard's rho algorithm, which uses modular addition
 *     - Trial division, which uses the Sieve of Atkin
 *     - Binary GCD algorithm, which is used by Pollard's rho algorithm
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 2/6/2018, 1:20am
 */

#include <cstdlib>
#include "factor_utils.h"


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
uint64_t gcd(uint64_t a, uint64_t b) {
    // Base cases
    if (a == b) return a;
    if (a == 0) return b;
    if (b == 0) return a;

    // Looking for factors of 2
    if (!(a & 1)) {  // a is even
        if (b & 1)   // b is odd
            return gcd(a >> 1, b);
        else         // b is also even
            return gcd(a >> 1, b >> 1) << 1;
    }

    if (!(b & 1))    // a is odd, b is even
        return gcd(a, b >> 1);

    if (a > b)
        return gcd((a - b) >> 1, b);
    else
        return gcd((b - a) >> 1, a);
}


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
std::map<uint64_t, uint64_t> trial_division(uint64_t n) {
    // Base case: If n < 2, return an empty map.
    std::map<uint64_t, uint64_t> factors;
    
    if (n < 2)
        return factors;
    
    // Get a list of primes.
    bool *is_prime = sieve_of_atkin(isqrt(n));
    
    // This loop runs for i in [2, isqrt(n)]:
    // 
    // Go through the list of integers (above), factoring out each prime value
    // from n completely. We stop once the square of our current prime exceeds
    // n.
    for (uint64_t i = 2; i <= isqrt(n); ++i) {
        if (is_prime[i]) {
            if (i*i > n) break;
            
            while (n % i == 0) {
                if (factors.find(i) != factors.end())
                    ++factors[i];
                else
                    factors.insert(std::map<uint64_t, uint64_t>::value_type(i, 1));
                n /= i;
            }
        }
    }
    
    // At this point, either n == 1 or n is itself a prime factor of the
    // original value. If the latter is true, we need to add that value to the
    // list of vectors as well.
    if (n > 1) {
        if (factors.find(n) != factors.end())
            ++factors[n];
        else
            factors.insert(std::map<uint64_t, uint64_t>::value_type(n, 1));
    }
    
    return factors;
}


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
uint64_t pollard(uint64_t n, uint64_t c) {
    // Initialize the following values:
    //     - t and h are the counters for the cycle-detection algorithm.
    //     - d is the factor that we will eventually return.
    uint64_t t = 2, h = 2, d = 1;
    
    // This loop runs until d is not 1. This means that d will either be a
    // non-trivial factor of n, or be equal to n.
    // 
    // t takes one step forward, and h takes two steps forward. We then compute
    // d by finding the greatest common divisor of the absolute value of t-h and
    // n.
    while (d == 1) {
        t = mod_add(t*t, c, n);
        h = mod_add(h*h, c, n);
        h = mod_add(h*h, c, n);
        d = gcd((t > h ? t-h : h-t), n);
    }
    
    // If d is still trivial (i.e., d == n), we increment our summand and start
    // over.
    if (d == n)
        return pollard(n, c + 1);
    else
        return d;
}
