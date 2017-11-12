/*
 * factor_utils.cpp: Function definitions for integer factorization. The following
 * methods are defined here:
 *     - Pollard's rho algorithm, with Floyd's cycle-detection algorithm 
 *     - Trial division, which uses the Sieve of Atkin
 *     - Greatest Common Divisor, which is used by Pollard's rho algorithm
 * Methods for the Dynamic Array are also defined here.
 *
 * Version:     1.2.0
 * License:     Public Domain
 * Author:      Joshua Morrison (jmorrison708@comcast.net)
 * Last Edited: 11/4/2017, 8:00pm
 */

#include <cstdlib>
#include "factor_utils.h"


/* Factorization Functions */

/**
 * gcd(): Greatest Common Divisor, as defined for Unsigned 64-bit Integers. This
 * specifically is the binary algorithm variant of GCD.
 *
 * Input:  uint64_t a, b - the numbers to calculate gcd() for.
 * Output: If b is 0, then we return a. Otherwise, we call gcd() recursively
 *         until we finally return a value.
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	// Base cases:
	if (a == b)
		return a;
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// Now we start looking for factors of 2.
	if (!(a & 1)) {   // a is even
		if (b & 1)  // b is odd
			return gcd(a >> 1, b);
		else            // b is also even
			return gcd(a >> 1, b >> 1) << 1;
	}

	if (!(b & 1))     // a is odd, b is even
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
    // Initialize the vector. If n < 2, just return the freshly allocated, empty
    // array.
    std::map<uint64_t, uint64_t> factors;
    if (n < 2)
        return factors;
    
    // Call the Sieve of Atkin to get a list of primes.
    bool *is_prime = sieve_atkin(isqrt(n));
    
    // This loop performs the following operations for all i in [2, isqrt(n)]:
    //     1. If is_prime[i] == TRUE, then do the following:
    //         a. If i^2 > n, exit the loop.
    //         b. Repeat while n is divisible by i:
    //             i. Append i to factors.
    //            ii. Let n = n / i.
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
    
    // At this point, either n == 1 or n is itself a prime factor of the original
    // value. If the latter is true, we need to add that value to the list of
    // vectors as well.
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
 *         uint64_t c - a constant value, which is used in calculations.
 * Output: A non-trivial, though not necessarily prime, factor of n.
 */
uint64_t pollard(uint64_t n, uint64_t c) {
    // Initialize the following values:
    //     - t and h are the main counters for the cycle-detection algorithm.
    //     - d is the factor of n that we will eventually return.
    uint64_t t = 2, h = 2, d = 1;
    
    // This loop performs the following operations:
    //     1. If d != 1, exit the loop.
    //     2. Let t = (t^2 + c) mod n.
    //     3. Let h = (h^2 + c) mod n. Repeat this operation once.
    //     4. Let d = gcd(abs(t - h), n).
    while (d == 1) {
		t = (t*t + c) % n;
		h = (h*h + c) % n;
		h = (h*h + c) % n;
		d = gcd((t > h ? t-h : h-t), n);
    }
    
    // At this point, d is either a non-trivial factor of n, or it is n. If the
    // latter is true, we must perform the algorithm again.
    if (d == n)
        return pollard(n, c + 1);
	else
		return d;
}