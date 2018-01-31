/*
 * primes.c: Prime Generation Utility. Generates a list of primes up to a given
 * bound.
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 7:00pm
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
 * isqrt(): Integer Square Root, as defined for Unsigned 64-bit Integers.
 *
 * Input:  uint32_t n - the number to take the square root of.
 * Output: A value equivalent to floor(sqrt(n)).
 */
uint32_t isqrt(uint32_t n) {
    // Base Case: if n < 2, then sqrt(n) == n, so just return n.
    if (n < 2) return n;
    
    // We calculate a "small" and "large" candidate for our return value:
    //     1. s, which is equal to 2 * isqrt(n / 4), is the small candidate.
    //     2. l, which is equal to one larger than s, is the large candidate.
    uint32_t s = isqrt(n >> 2) << 1;
    uint32_t l = s + 1;
    
    if (l*l > n)  // l is too big, so s is the value we want
        return s;
    else
        return l;
}

/**
 * sieve(): Sieve of Atkin. Returns a list of boolean values, where true
 * denotes a prime number and false denotes a composite number. This algorithm
 * is, in essence, an improvement of the Sieve of Eratosthenes.
 *
 * Input:  uint32_t n - the upper bound for sieving.
 * Output: An array as described above.
 */
bool *sieve(uint32_t n) {
    // calloc() initializes each cell to 0, which makes our setup much easier.
    bool *data = calloc(n + 1, sizeof(bool));
    data[2] = true;
    data[3] = true;
    uint32_t lim = isqrt(n);
    
    // This loop runs for all x in [1, lim].
    for (uint32_t x = 1; x <= lim; ++x) {
        // This loop runs for all y in [1, lim].
        // 
        // k is prime if any of the following are true:
        //     1. For k = 4*x^2 + y^2, k is prime iff k mod 12 = 1 or 5.
        //     2. For k = 3*x^2 + y^2, k is prime iff k mod 12 = 7.
        //     3. For k = 3*x^2 - y^2, k is prime iff k mod 12 = 11.
        // All of these also assume that k is not greater than n, and for the
        // third case, that k is not negative (i.e., that x > y).
        for (uint32_t y = 1; y <= lim; ++y) {
            uint32_t k = (4*x*x) + (y*y);
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
    for (uint32_t j = 5; j <= lim; ++j) {
        if (data[j]) {
            for (uint32_t k = j*j; k <= n; k += j*j)
                data[k] = false;
        }
    }
    
    return data;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: primes n\n");
        printf("\tn: Bound for the sieve (Max 2^32 - 1)\n\n");
        printf("Generate a list of primes below a given bound.\n");
        exit(EXIT_FAILURE);
    }
    
    // NOTE: we limit n to a 32-bit integer because of the limitations of arrays
    // in C/C++. At most, an array can hold SIZE_MAX elements, which is equal to
    // the upper limit of uint32_t.
    char *cend;
    uint32_t n = (uint32_t) strtoul(argv[1], &cend, 10);
    FILE *primes_file = fopen("primes.txt", "w");
    uint32_t count = 0;
    
    clock_t start = clock();
    bool *is_prime = sieve(n);
    
    uint32_t k;
    for (k = 0; k <= n; ++k) {
        if (is_prime[k]) {
            fprintf(primes_file, "%lu\n", k);
            ++count;
        }
    }
    
    fclose(primes_file);
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    
    printf("%lu primes found below %lu in %.6f seconds\n", count, n, time);
}