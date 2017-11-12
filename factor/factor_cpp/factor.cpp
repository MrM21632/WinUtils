/*
 * factor.cpp: Main method and algorithm for Factorization utility.
 *
 * Version:     1.2.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/4/2017, 8:00pm
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "factor_utils.h"

// Number of iterations for each primality test; it's large enough to account for
// any weird output the test could give.
#define TEST_NUM (30)


/**
 * factor(): Main factorization method.
 *
 * Input:  uint64_t n - the number to factorize.
 * Output: A dynamic_array of n's factors.
 */
std::map<uint64_t, uint64_t> factor(uint64_t n) {
    // First, we handle the base cases.
    //     1. If n <= 1, return an empty array.
    //     2. If n <= 3, return {n}.
    std::map<uint64_t, uint64_t> n_factors;
    if (n <= 1)
        return n_factors;
    else if (n <= 3) {
        n_factors.insert(std::map<uint64_t, uint64_t>::value_type(n, 1));
        return n_factors;
    }
    
    // Miller-Rabin requires n be odd, so we need to divide n by 2 until what
    // remains is an odd integer.
    // 
    // Once we do this, we check to see if n == 1 or n is prime. If either is
    // true, we're ready to terminate the method.
    while (!(n & 1)) {  // Equivalent to "n % 2 == 0"
        if (n_factors.find(2) != n_factors.end())
            ++n_factors[2];
        else
            n_factors.insert(std::map<uint64_t, uint64_t>::value_type(2, 1));

        n >>= 1;
    }
    if (n == 1)
        return n_factors;
    else if (is_prime(n, TEST_NUM)) {
        // If n is prime at this point, it is guaranteed not to be in the map at
        // this point, so we can insert it without worry.
        n_factors.insert(std::map<uint64_t, uint64_t>::value_type(n, 1));
        return n_factors;
    }
    
    // At this point, we know that n is an odd integer greater than 1. This loop
    // performs the following operations:
    //     1. If n == 1 or n is prime, exit the loop.
    //     2. Let f = pollard(n, 1). If f is prime, append f to n_factors.
    //        Otherwise, let f_factors = trial_div(f), and append the contents
    //        of f_factors to n_factors.
    //     3. Let n = n / f.
    while (n > 1 && !is_prime(n, TEST_NUM)) {
        uint64_t f = pollard(n, 1);
        
        if (is_prime(f, TEST_NUM)) {
            if (n_factors.find(f) != n_factors.end())
                ++n_factors[f];
            else
                n_factors.insert(std::map<uint64_t, uint64_t>::value_type(f, 1));
        }
        else {
            std::map<uint64_t, uint64_t> f_factors = trial_div(f);

            // Now we iterate through f_factors and add to n_factors as needed.
            for (std::map<uint64_t, uint64_t>::iterator it = f_factors.begin(); it != f_factors.end(); ++it) {
                if (n_factors.find(it->first) != n_factors.end())
                    n_factors[it->first] += it->second;
                else
                    n_factors.insert(std::map<uint64_t, uint64_t>::value_type(it->first, it->second));
            }
        }
        
        n /= f;
    }
    
    // If, at this point, n is not 1, then it is either a prime factor, or it
    // still needs to be factored.
    if (n != 1) {
        if (is_prime(n, TEST_NUM)) {
            if (n_factors.find(n) != n_factors.end())
                ++n_factors[n];
            else
                n_factors.insert(std::map<uint64_t, uint64_t>::value_type(n, 1));
        }
        else {
            std::map<uint64_t, uint64_t> n_n_factors = trial_div(n);
            
            // n_factors.insert(n_factors.end(), n_n_factors.begin(), n_n_factors.end());
            for (std::map<uint64_t, uint64_t>::iterator it = n_n_factors.begin(); it != n_n_factors.end(); ++it) {
                if (n_factors.find(it->first) != n_factors.end())
                    n_factors[it->first] += it->second;
                else
                    n_factors.insert(std::map<uint64_t, uint64_t>::value_type(it->first, it->second));
            }
        }
    }
    
    return n_factors;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        std::printf("Usage: factor [n]\n");
        std::printf("\tn: Integer to be factored (no larger than 2^64-1)\n\n");
        std::printf("Determines and outputs the prime factorization of a given integer.\n");
        std::exit(EXIT_FAILURE);
    }
    
    char *e;
    uint64_t n = std::strtoull(argv[1], &e, 10);
    
    clock_t start = std::clock();
    std::printf("Processing... ");
    std::map<uint64_t, uint64_t> factors = factor(n);
    clock_t end = std::clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::printf("Done. Factorization took %.6f seconds.\n\n", time);
    
    if (factors.size() == 0) {
        std::printf("Factors of %llu: N/A\n", n);
        std::exit(EXIT_SUCCESS);
    }

    std::map<uint64_t, uint64_t>::iterator it = factors.begin();
    std::printf("Factors of %llu: ", n);
    if (it->second == 1)
        std::printf("%llu", it->first);
    else
        std::printf("%llu^%llu", it->first, it->second);
    ++it;
    if (factors.size() == 1) {
        std::printf("\n");
        std::exit(EXIT_SUCCESS);
    }

    for (; it != factors.end(); ++it) {
        if (it->second == 1)
            std::printf(", %llu", it->first);
        else
            std::printf(", %llu^%llu", it->first, it->second);
    }
    std::printf("\n");
}