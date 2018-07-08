/*
 * prime_utils.cpp: Function definitions for working with primes. The following
 * methods are defined here:
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

#include <cstdlib>
#include <random>
// #include <boost/random/mersenne_twister.hpp>
// #include <boost/random/random_device.hpp>
// #include <boost/random/uniform_int_distribution.hpp>
#include "prime_utils.h"


uint64_t isqrt(uint64_t n) {
    // Base Case: if n < 2, then sqrt(n) = n.
    if (n < 2) return n;
    
    // We calculate a "small" and "large" candidate for our return value:
    //     1. s, which is equal to 2 * isqrt(n / 4), is the small candidate.
    //     2. l, which is equal to one larger than s, is the large candidate.
    uint64_t s = isqrt(n >> 2) << 1;
    uint64_t l = s + 1;
    
    if (l*l > n)
        return s;
    else
        return l;
}


uint64_t mod_add(uint64_t a, uint64_t b, uint64_t n) {
    return ((a % n) + (b % n)) % n;
}


uint64_t mod_mult(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 0;  // Remainder
    
    // If a is larger than the modulus, we need to reduce it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;
    
    // Perform modular addition on r until the multiplier is 0.
    while (b > 0) {
        if (b & 1)
            r = mod_add(r, a, n);
        
        a = (a * 2) % n;
        b >>= 1;
    }
    
    // (a * b) mod n == ((a mod n) * (b mod n)) mod n. At this point, we have
    // calculated r = (a mod n) * (b mod n), so we now need to reduce r by mod
    // n, then return that result.
    return r % n;
}


uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 1;  // Remainder
    
    // If a is larger than the modulus, we need to reduce it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;
    
    // Perform modular multiplication on both the remainder and the base, until
    // our exponent is 0.
    while (b > 0) {
        if (b & 1)
            r = mod_mult(r, a, n);
        
        a = mod_mult(a, a, n);
        b >>= 1;
    }
    
    return r;
}


bool miller_rabin(uint64_t n, uint64_t d) {
    // boost::random::random_device rd;
    // boost::random::mt19937 mt(rd());
    // boost::random::uniform_int_distribution<uint64_t> dist(2, n-2);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<uint64_t> dist(2, n-2);
    
    uint64_t a = dist(mt);
    uint64_t x = mod_pow(a, d, n);
    
    // Base Case: if a^d mod n is 1 or n-1, then we already know n is prime, so
    // we can return true.
    if (x == 1 || x == n-1)
        return true;
    
    // Perform modular multiplication on x until d is equal to n-1.
    while (d != (n - 1)) {
        x = mod_mult(x, x, n);
        d <<= 1;
        
        if (x == 1) return false;
        if (x == (n - 1)) return true;
    }
    
    // If we reach this point, we can safely say that n is not prime, so we
    // return false.
    return false;
}


bool is_prime(uint64_t n, uint64_t k) {
    // Base cases
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (!(n & 1)) return false;
    
    // At this point, we know n is odd and greater than 1. Now, our goal is to
    // find an integer d such that n-1 = d * 2^r, where r >= 1. The loop divides
    // d by 2 until it is no longer even - at that point, we will have the value
    // we desire.
    uint64_t d = n - 1;
    while (!(d & 1))
        d >>= 1;
    
    // Call miller_rabin(n, d) k times. If any of the tests fail, we know that n
    // is not prime, so we return false.
    for (uint64_t i = 0; i < k; ++i) {
        if (!miller_rabin(n, d))
            return false;
    }
    
    // If we reach this point, we can safely assume (NOT guarantee!) n is prime,
    // so we return true.
    return true;
}


bool *sieve_of_atkin(uint64_t n) {
    // The new[] operator in C++ makes setup very easy for us.
    bool *data = new bool[n + 1]();
    data[2] = true;
    data[3] = true;
    uint64_t lim = isqrt(n);
    
    // This loop runs for all x in [1, lim].
    for (uint64_t x = 1; x <= lim; ++x) {
        // This loop runs for all y in [1, lim].
        // 
        // k is prime if any of the following are true:
        //     1. For k = 4*x^2 + y^2, k is prime iff k mod 12 = 1 or 5.
        //     2. For k = 3*x^2 + y^2, k is prime iff k mod 12 = 7.
        //     3. For k = 3*x^2 - y^2, k is prime iff k mod 12 = 11.
        // All of these also assume that k is not greater than n, and for the
        // third case, that k is not negative (i.e., that x > y).
        for (uint64_t y = 1; y <= lim; ++y) {
            uint64_t k = (4*x*x) + (y*y);
            if ((k <= n) && ((k % 12 == 1) || (k % 12 == 5)))
                data[k] = !data[k];
            
            k = (3*x*x) + (y*y);
            if ((k <= n) && (k % 12 == 7))
                data[k] = !data[k];
            
            k = (3*x*x) - (y*y);
            if ((x > y) && (k <= n) && (k % 12 == 11))
                data[k] = !data[k];
        }
    }
    
    // This loop runs for all j in [5, lim].
    // 
    // We perform one last loop through the array. If j is prime, then we mark
    // all multiples of its square as composite, a la the standard Sieve of
    // Eratosthenes.
    for (uint64_t j = 5; j <= lim; ++j) {
        if (data[j]) {
            for (uint64_t k = j*j; k <= n; k += j*j)
                data[k] = false;
        }
    }
    
    return data;
}
