/*
 * prime_utils.cpp: Function definitions for working with primes. The following
 * methods are defined here:
 *     - Miller-Rabin Probabilistic Primality Test, with an iterative tester
 *       method
 *     - Modular Addition, which is used by the modular multiplication algorithm
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

#include <cstdlib>
#include <random>
#include "prime_utils.h"


/**
 * isqrt(): Integer Square Root, as defined for Unsigned 64-bit Integers.
 *
 * Input:  uint64_t n - the number to find the square root of.
 * Output: floor(sqrt(n)).
 */
uint64_t isqrt(uint64_t n) {
    // Base Case: if n < 2, then sqrt(n) == n, so just return n.
    if (n < 2) return n;
    
    // Calculate two different forms of the square root:
    //     1. s, which involves a recursive call of isqrt(), and
    //     2. l, which is simply one larger than s.
    uint64_t s = isqrt(n >> 2) << 1;
    uint64_t l = s + 1;
    
    // Check to see which calculation is floor(sqrt(n)). If l^2 is larger, then
    // s is the value we want to return. Otherwise, return l.
    if (l*l > n)
        return s;
    else
        return l;
}

/**
 * mod_add(): Modular Addition, as defined for Unsigned 64-bit Integers.
 *
 * Input:  uint64_t a, b - the addends/summands/terms/etc.
 *         uint64_t n - the modulus.
 * Output: (a + b) mod n.
 */
uint64_t mod_add(uint64_t a, uint64_t b, uint64_t n) {
    return ((a % n) + (b % n)) % n;
}

/**
 * mod_mult(): Modular Multiplication, as defined for Unsigned 64-bit Integers.
 * 
 * Input:  uint64_t a, b - the multiplicand and multiplier, respectively.
 *         uint64_t n - the modulus.
 * Output: (a * b) mod n.
 */
uint64_t mod_mult(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 0;  // Our resulting calculation, to return
    
    // If a is larger than the modulus, we need to truncate it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;
    
    // This loop performs the following operation:
    //     1. If b <= 0, exit the loop.
    //     2. if b is odd, let r = (r + a), then truncate r by performing
    //        mod n on it.
    //     3. Let a = 2*a, then truncate a by performing mod n on it.
    //     4. Let b = b / 2.
    while (b > 0) {
        if (b & 1)  // Equivalent to "b % 2 == 1"
            r = mod_add(r, a, n);
        
        a = (a * 2) % n;
        b >>= 1;    // Equivalent to "b /= 2"
    }
    
    // NOTE: (a * b) mod n == ((a mod n) * (b mod n)) mod n. At this point, we
    // have calculated r = (a mod n) * (b mod n), so we now need to truncate r
    // by n, then return that result.
    return r % n;
}

/**
 * mod_pow(): Modular Exponentiation, as defined for Unsigned 64-bit Integers.
 *
 * Input:  uint64_t a, b - the base and exponent, respectively.
 *         uint64_t n - the modulus.
 * Output: a^b mod n.
 */
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 1;  // Our resulting calculation, to return
    
    // If a is larger than the modulus, we need to truncate it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;
    
    // This loop performs the following operation:
    //     1. If b <= 0, exit the loop.
    //     2. If b is odd, let r = (r * a) mod n. In order to avoid overflow, we
    //        use mod_mult().
    //     3. Let b = b / 2.
    //     4. Let a = a^2 mod n.
    while (b > 0) {
        if (b & 1)  // Equivalent to "b % 2 == 1"
            r = mod_mult(r, a, n);
        
        a = mod_mult(a, a, n);
        b >>= 1;    // Equivalent to "b /= 2"
    }
    
    return r;
}

/**
 * miller_rabin(): Main algorithm for the Miller-Rabin primality test. Returns a
 * probabilistic "guess" of whether or not n is prime.
 *
 * Input:  uint64_t n - the number to test for primality.
 *         uint64_t d - an odd integer > 1, such that n - 1 = d * 2^r for some integer
 *                  r > 1.
 * Output: true if n is (likely) prime, or false if n is composite.
 */
bool miller_rabin(uint64_t n, uint64_t d) {
    // Variables for random number generation
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<uint64_t> dist(2, n-2);
    
    uint64_t a = dist(mt);          // Randomly select a from [2, n-2]
    uint64_t x = mod_pow(a, d, n);  // Let x = a^d mod n
    
    // Base Case: if a^d mod n is 1 or n-1, then we already know n is prime, so
    // we can return true.
    if (x == 1 || x == n-1)
        return true;
    
    // This loop performs the following operation:
    //     1. If d == n-1, exit the loop.
    //     2. Let x = x^2 mod n.
    //     3. Let d = 2 * d.
    //     4. If x == 1, return true. If x == n-1, return true.
    while (d != (n - 1)) {
        x = mod_mult(x, x, n);
        d <<= 1;  // Equivalent to "d *= 2"
        
        if (x == 1) return false;
        if (x == (n - 1)) return true;
    }
    
    // If we reach this point, we can safely say that n is not prime, so we
    // return false.
    return false;
}

/**
 * is_prime(): Function that calls miller_rabin() a number of times, as a means
 * of improving the accuracy of the test.
 *
 * Input:  uint64_t n - the number to test for primality.
 *         uint64_t k - the number of times to repeat the test.
 * Output: true if every test succeeds, false otherwise.
 */
bool is_prime(uint64_t n, uint64_t k) {
    // Base Case: If n <= 1, we already know n is not prime.
    if (n <= 1) return false;
    // Base Case: If n <= 3, we know n is prime.
    if (n <= 3) return true;
    // Base Case: If n is even, we know n is not prime.
    if (!(n & 1)) return false;
    
    // At this point, we know n is odd and greater than 1. Now, our goal is to
    // find an integer d such that n-1 = d * 2^r, where r >= 1. The loop divides
    // d by 2 until it is no longer even - at that point, we will have the value
    // we desire.
    uint64_t d = n - 1;
    while (!(d & 1))  // Equivalent to "d % 2 == 0"
        d >>= 1;      // Equivalent to "d /= 2"
    
    // This loop calls miller_rabin(n, d) k times. If any of the tests fail, we
    // know that n is not prime, so we return false.
    for (uint64_t i = 0; i < k; ++i) {
        if (!miller_rabin(n, d))
            return false;
    }
    
    // If we reach this point, we can safely assume (NOT guarantee!) n is prime,
    // so we return true.
    return true;
}

/**
 * sieve_atkin(): Sieve of Atkin. Returns a list of boolean values, where TRUE
 * denotes a prime number and FALSE denotes a composite number.
 *
 * Input:  uint64_t n - the upper most bound for sieving.
 * Output: An array as described above.
 */
bool *sieve_atkin(uint64_t n) {
    // First, we allocate the array of booleans and instantiate it as needed.
    // Thankfully, all we need to do in C++ is create a new bool[](), which
    // will initialize all values to false. Then, we simply make data[2] and
    // data[3] true.
    bool *data = new bool[n + 1]();
    data[2] = true;
    data[3] = true;
    
    // We also need isqrt(n), as a bound for the iterations below.
    uint64_t lim = isqrt(n);
    
    // This loop runs for all x in [1, lim].
    for (uint64_t x = 1; x <= lim; ++x) {
        // This loop performs the following operations for all y in [1, lim]:
        //     1. Let k = 4*x^2 + y^2.
        //     2. If k <= n then do the following:
        //         a. If k mod 12 == 1 or 5, then flip data[k]'s value. (NOTE that
        //            ! will return 0 (false) if the value given to it is 0)
        //     3. Let k = 3*x^2 + y^2.
        //     4. If k <= n then do the following:
        //         a. If k mod 12 == 7, then flip data[k]'s value.
        //     5. Let k = 3*x^2 - y^2.
        //     6. If k <= n and x > y then do the following:
        //         a. If k mod 12 == 11, then flip data[k]'s value.
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
    
    // This loop performs the following operations for all j in [5, lim]:
    //     1. If data[j] == TRUE, then do the following:
    //         a. Repeat for all k in [j^2, n], step j^2:
    //             i. Let data[k] = false.
    for (uint64_t j = 5; j <= lim; ++j) {
        if (data[j]) {
            for (uint64_t k = j*j; k <= n; k += j*j)
                data[k] = false;
        }
    }
    
    return data;
}