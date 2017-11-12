/*
 * gcd_lcm.cpp: Math Utility #1. Computes the greatest common divisor (GCD) and
 * least common multiple (LCM) of two integers. For this program, we will limit
 * the user to only signed 64-bit integers, as there (likely) won't be much need
 * for anything larger to be calculated.
 *
 * Version:     1.0.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/5/2017, 11:30am
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>


/**
 * b_abs(): Calculate the absolute value of n via bitwise operations.
 *
 * Input:  int64_t n - the number to perform the operation on.
 * Output: |n|.
 */
int64_t b_abs(int64_t n) {
    int64_t mask = n >> sizeof(int64_t) * CHAR_BIT - 1;
    return (n + mask) ^ mask;
}

/**
 * gcd_bin(): Greatest Common Divisor, as defined for Unsigned 64-bit Integers.
 * This specifically is the Binary GCD Algorithm, which is significantly faster
 * for large integers than the standard iterative and recursive definitions.
 *
 * Input:  uint64_t a, b - the numbers to calculate gcd() for.
 * Output: If b is 0, then we return a; the reverse applies as well. Otherwise,
 *         we call gcd() recursively until we finally return a value.
 */
int64_t gcd_bin(int64_t a, int64_t b) {
    // We know that gcd(a, b) = gcd(|a|, |b|), so we only need the absolute
    // values of a and b to calculate the GCD.
    if (a < 0) a = b_abs(a);
    if (b < 0) b = b_abs(b);

    // Base cases:
    if (a == b)
        return a;
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    // Now we start looking for factors of 2.
    if (!(a & 1)) {  // a is even
        if (b & 1)   // b is odd
            return gcd_bin(a >> 1, b);
        else         // b is also even
            return gcd_bin(a >> 1, b >> 1) << 1;
    }

    if (!(b & 1))    // a is odd, b is even
        return gcd_bin(a, b >> 1);

    if (a > b)
        return gcd_bin((a - b) >> 1, b);
    else
        return gcd_bin((b - a) >> 1, a);
}

/**
 * lcm(): Least Common Multiple, as defined for Unsigned 64-bit Integers.
 *
 * Input:  uint64_t a, b - the numbers to calculate lcm() for.
 * Output: The properly calculated lcm(a,b).
 */
int64_t lcm(int64_t a, int64_t b) {
    // We know that lcm(a, b) = lcm(|a|, |b|), so we only need the absolute
    // values of a and b to calculate the LCM.
    if (a < 0) a = b_abs(a);
    if (b < 0) b = b_abs(b);

    // The standard definition of LCM is ab / gcd(a,b). However, to avoid
    // overflow, we use the following calculation:
    return (a / gcd_bin(a, b)) * b;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        std::printf("Usage: gcd_lcm [a] [b]\n");
        std::printf("\ta,b: In the range [-2^63, 2^63)\n\n");
        std::printf("Compute GCD and LCM for integers a and b.\n");
        std::exit(EXIT_FAILURE);
    }

    // Parse a and b from STDIN
    char *e, *f;
    int64_t a = std::strtoll(argv[1], &e, 10);
    int64_t b = std::strtoll(argv[2], &f, 10);
    
    // Calculate GCD
    clock_t start = std::clock();
    int64_t g = gcd_bin(a, b);
    clock_t end = std::clock();
    double time1 = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Calculate LCM
    start = std::clock();
    int64_t l = lcm(a, b);
    end = std::clock();
    double time2 = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Output the results
    std::printf("gcd(%lld, %lld) = %lld (process took %.6f seconds)\n", a, b, g, time1);
    std::printf("lcm(%lld, %lld) = %lld (process took %.6f seconds)\n", a, b, l, time2);
}