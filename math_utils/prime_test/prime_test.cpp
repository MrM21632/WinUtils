/*
 * prime_test.cpp: Math Utility #6. Determine if the given integer is prime, then
 * find and output the next prime starting from the same integer.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <random>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

// Constant value used for testing primality; ensures we won't run into any
// unepxected results.
#define TEST_NUM (30)

// Constants for random number generation
std::random_device rd;
std::mt19937 mt(rd());


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
uint64_t mod_add(uint64_t a, uint64_t b, uint64_t n) {
    return ((a % n) + (b % n)) % n;
}

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
uint64_t mod_mult(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 0;  // Remainder, to be returned

    // If a is larger than the modulus, we need to reduce it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;

    // This loop performs modular addition on r until the multiplier is 0.
    while (b > 0) {
        if (b & 1)  // Equivalent to "b % 2 == 1"
            r = mod_add(r, a, n);

        a = (a * 2) % n;
        b >>= 1;    // Equivalent to "b /= 2"
    }

    // (a * b) mod n == ((a mod n) * (b mod n)) mod n. At this point, we have
    // calculated r = (a mod n) * (b mod n), so we now need to reduce r by mod
    // n, then return that result.
    return r % n;
}

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
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t r = 1;  // Remainder, to be returned

    // If a is larger than the modulus, we need to reduce it in order to avoid
    // integer overflow.
    if (a >= n) a %= n;

    // This loop performs modular multiplication on both the remainder and the
    // base, until our exponent is 0.
    while (b > 0) {
        if (b & 1)  // Equivalent to "b % 2 == 1"
            r = mod_mult(r, a, n);

        a = mod_mult(a, a, n);
        b >>= 1;    // Equivalent to "b /= 2"
    }

    return r;
}

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
bool miller_rabin(uint64_t n, uint64_t d) {
    std::uniform_int_distribution<uint64_t> dist(2, n - 2);

    uint64_t a = dist(mt);          // Randomly select a from [2, n-2]
    uint64_t x = mod_pow(a, d, n);  // Let x = a^d mod n

    // Base Case: if a^d mod n is 1 or n-1, then we can already assume n is
    // prime, so we can return true.
    if (x == 1 || x == n - 1)
        return true;

    // This loop performs modular multiplication on x until d is equal to n-1.
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
bool is_prime(uint64_t n, uint64_t k) {
    // Base cases
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (!(n & 1)) return false;  // Equivalent to "n % 2 == 0"

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
 *  @brief Find the Next Prime
 *  
 *  @param [in] n Start point for prime search
 *  @return The next prime number after n.
 *  
 *  @details Looks for the next prime number to occur after the given integer.
 */
uint64_t next_prime(uint64_t n) {
    // This loop runs for all i in [n+1, inf).
    // 
    // Because there is consistently a marginal number of integers between any
    // two primes, this process will execute quickly.
    for (uint64_t i = n + 1; ; ++i) {
        if (is_prime(i, TEST_NUM))
            return i;
    }
}


int main(int argc, char **argv) {
    if (argc != 2) {
        std::printf("Usage: prime_test n\n");
        std::printf("\tn: Number to test; in range [0, 2^64)\n\n");
        std::printf("Test the given number for primality, then find the next prime number.\n");
        std::exit(EXIT_FAILURE);
    }

    char *e;
    uint64_t n = std::strtoull(argv[1], &e, 10);

    clock_t start = std::clock();
    bool is_n_prime = is_prime(n, TEST_NUM);
    uint64_t next = next_prime(n);
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::printf("%llu is %s.\n", n, (is_n_prime ? "PRIME" : "NOT PRIME"));
    std::printf("The next prime is %llu.\n", next);
    std::printf("Process took %.6f seconds.\n", time);
}
