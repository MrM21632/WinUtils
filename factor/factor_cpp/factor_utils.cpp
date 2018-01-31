/*
 * factor_utils.cpp: Function definitions for integer factorization. The
 * following methods are defined here:
 *     - Pollard's rho algorithm, which uses modular addition
 *     - Trial division, which uses the Sieve of Atkin
 *     - Binary GCD algorithm, which is used by Pollard's rho algorithm
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <cstdlib>
#include "factor_utils.h"


/**
 * gcd(): Greatest Common Divisor, as defined for Unsigned 64-bit Integers. This
 * specifically is the binary algorithm for calculating GCD.
 *
 * Input:  uint64_t a, b - the numbers to calculate gcd() for.
 * Output: If either a or b is 0, then we return the other value. Otherwise, we
 *         call gcd() recursively until we can return a value.
 */
uint64_t gcd(uint64_t a, uint64_t b) {
    // Base cases
    if (a == b)
        return a;
    if (a == 0)
        return b;
    if (b == 0)
        return a;

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
 * trial_div(): Trial Division. Computes the factors of a given integer, and
 * returns them in a vector.
 *
 * Input:  uint64_t n - the number to be factored.
 * Output: A vector<uint64_t> as described above.
 */
std::map<uint64_t, uint64_t> trial_div(uint64_t n) {
    // Base case: If n < 2, return an empty map.
    std::map<uint64_t, uint64_t> factors;
    
    if (n < 2)
        return factors;
    
    // Get a list of primes.
    bool *is_prime = sieve_atkin(isqrt(n));
    
    // This loop runs for i in [2, isqrt(n)]:
    // 
    // Go through the list of integers (above), factoring out each prime value
    // from n. We stop once the square of our current prime exceeds n.
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
 * pollard(): Pollard's rho algorithm.
 *
 * Input:  uint64_t n - the number to be factored.
 *         uint64_t c - a "constant" used for calculations.
 * Output: A non-trivial, though not necessarily prime, factor of n.
 */
uint64_t pollard(uint64_t n, uint64_t c) {
    // Initialize the following values:
    //     - t and h are the counters for the cycle-detection algorithm.
    //     - d is the factor that we will eventually return.
    uint64_t t = 2, h = 2, d = 1;
    
    // This loop runs until d is not 1. This means that d will either be a
    // non-trivial factor of n, or be equal to n.
    while (d == 1) {
        t = mod_add(t*t, c, n);
        h = mod_add(h*h, c, n);
        h = mod_add(h*h, c, n);
        d = gcd((t > h ? t-h : h-t), n);
    }
    
    if (d == n)
        return pollard(n, c + 1);
    else
        return d;
}