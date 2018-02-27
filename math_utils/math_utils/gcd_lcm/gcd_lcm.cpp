/*
 * gcd_lcm.cpp: Math Utility #1. Computes the greatest common divisor (GCD) and
 * least common multiple (LCM) of two non-negative integers. For this program,
 * we will limit the user to only unsigned 64-bit integers, as there (likely)
 * won't be much need for anything larger to be calculated.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>


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
uint64_t gcd_bin(uint64_t a, uint64_t b) {
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
 *  @brief Least Common Multiple
 *  
 *  @param [in] a Operand
 *  @param [in] b Operand
 *  @return lcm(a, b).
 *  
 *  @details Computes the least common multiple (LCM) of two integers. This
 *           definition uses a small trick to avoid overflow.
 */
uint64_t lcm(uint64_t a, uint64_t b) {
    // The standard definition of LCM is ab / gcd(a,b). However, to avoid
    // overflow, we use the following calculation:
    return (a / gcd_bin(a, b)) * b;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        std::printf("Usage: gcd_lcm a b\n");
        std::printf("\ta,b: In the range [0, 2^64)\n\n");
        std::printf("Compute GCD and LCM for non-negative integers a and b.\n");
        return EXIT_FAILURE;
    }

    // Parse a and b from STDIN
    char *e, *f;
    uint64_t a = std::strtoll(argv[1], &e, 10);
    uint64_t b = std::strtoll(argv[2], &f, 10);
    
    // Calculate GCD
    clock_t start = std::clock();
    uint64_t g = gcd_bin(a, b);
    clock_t end = std::clock();
    double time1 = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Calculate LCM
    start = std::clock();
    uint64_t l = lcm(a, b);
    end = std::clock();
    double time2 = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Output the results
    std::printf("gcd(%llu, %llu) = %llu (process took %.6f seconds)\n", a, b, g, time1);
    std::printf("lcm(%llu, %llu) = %llu (process took %.6f seconds)\n", a, b, l, time2);
}
