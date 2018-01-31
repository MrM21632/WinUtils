/*
 * perm_comb.cpp: Math Utility #2. Given the cardinality of a set of numbers (n)
 * and the number of elements to select from the set (r), compute the following:
 *     1. The total number of permutations of the set.
 *     2. The total number of r-combinations for all r of the set.
 *     3. The r-permutation of the set, P(n,r), both allowing and not allowing
 *        repetition of elements in the set.
 *     4. The r-combination of the set, C(n,r), both allowing and not allowing
 *        repetition of elements in the set.
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mpir.h>


/**
 * perm_all(): Compute the total number of permutations for a set with given
 * cardinality n.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality (i.e., number of elements) of the set.
 * Output: N/A. The calculation is stored in res.
 */
void perm_all(mpz_t res, mpir_ui n) {
    // As it turns out, the desired value is exactly equal to n!, so all we need
    // to do is calculate that.
    mpz_fac_ui(res, n);
}

/**
 * comb_all(): Compute the total number of r-permutations for all r for a set
 * with given cardinality n.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality of the set.
 * Output: N/A. The calculation is stored in res.
 */
void comb_all(mpz_t res, mpir_ui n) {
    // As it turns out, the desired value is exactly equal to 2^n, so all we need
    // to do is calculate that.
    mpz_ui_pow_ui(res, static_cast<mpir_ui>(2), n);
}

/**
 * perm_no_rep(): Compute the r-permutation of a set with given cardinality n,
 * P(n, r), where repetition of elements is not allowed.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality of the set.
 *         mpir_ui r - the number of elements to select from the set.
 * Output: N/A. The calculation is stored in res.
 */
void perm_no_rep(mpz_t res, mpir_ui n, mpir_ui r) {
    // Initialize res to 1.
    mpz_set_ui(res, static_cast<mpir_ui>(1));

    // This loop performs the following operation for all i in (n-r, n], step down:
    //     1. Multiply the value contained in res by i.
    for (mpir_ui i = n; i > n - r; --i)
        mpz_mul_ui(res, res, i);
}

/**
 * perm_rep(): Compute the r-permutation of a set with given cardinality n,
 * P(n, r), where repetition of elements is allowed.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality of the set.
 *         mpir_ui r - the number of elements to select from the set.
 * Output: N/A. The calculation is stored in res. 
 */
void perm_rep(mpz_t res, mpir_ui n, mpir_ui r) {
    // As it turns out, the desired value is exactly equal to n^r, so all we need
    // to do is calculate that.
    mpz_ui_pow_ui(res, n, r);
}

/**
 * comb_no_rep(): Compute the r-combination of a set with given cardinality n,
 * C(n, r), where repetition of elements is not allowed.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality of the set.
 *         mpir_ui r - the number of elements to select from the set.
 * Output: N/A. The calculation is stored in res. 
 */
void comb_no_rep(mpz_t res, mpir_ui n, mpir_ui r) {
    // C(n, r) is equivalent to the binomial coefficient "n choose r" when
    // repetition is not allowed.
    mpz_bin_uiui(res, n, r);
}

/**
 * comb_rep(): Compute the r-combination of a set with given cardinality n,
 * C(n, r), where repetition of elements is allowed.
 *
 * Input:  mpz_t res - arbitrary-precision integer that holds the calculation.
 *         mpir_ui n - the cardinality of the set.
 *         mpir_ui r - the number of elements to select from the set.
 * Output: N/A. The calculation is stored in res. 
 */
void comb_rep(mpz_t res, mpir_ui n, mpir_ui r) {
    // C(n, r) is equivalent to "n multichoose r", or the binomial coefficient
    // "[(n + r) - 1] choose r" when repetition is allowed.
    mpz_bin_uiui(res, (n + r) - 1, r);
}


int main(int argc, char **argv) {
    if (argc != 3) {
        std::printf("Usage: perm_comb n r\n");
        std::printf("\tn: Number of elements to choose from.\n");
        std::printf("\tr: Number of elements to choose.\n");
        std::printf("\tNOTE: both n and r are limited to [0, 2^64).\n\n");
        std::printf("Compute various fundamental combinatoric values.\n");
        std::exit(EXIT_FAILURE);
    }

    // Get the values from argv
    char *e, *f;
    mpir_ui n = static_cast<mpir_ui>(std::strtoull(argv[1], &e, 10));
    mpir_ui r = static_cast<mpir_ui>(std::strtoull(argv[2], &f, 10));

    // Setup the arbitrary-precision integers.
    //     1. pa: perm_all()
    //     2. pn: perm_no_rep()
    //     3. pr: perm_rep()
    //     4. ca: comb_all()
    //     5. cn: comb_no_rep()
    //     6. cr: comb_rep()
    mpz_t pa, pn, pr, ca, cn, cr;
    mpz_inits(pa, pn, pr, ca, cn, cr, NULL);

    // Perform the calculations.
    clock_t start = std::clock();
    perm_all(pa, n);
    comb_all(ca, n);
    perm_no_rep(pn, n, r);
    comb_no_rep(cn, n, r);
    perm_rep(pr, n, r);
    comb_rep(cr, n, r);
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Convert the results to strings, for ease of output.
    char *pa_str = mpz_get_str(NULL, 10, pa);
    char *pn_str = mpz_get_str(NULL, 10, pn);
    char *pr_str = mpz_get_str(NULL, 10, pr);
    char *ca_str = mpz_get_str(NULL, 10, ca);
    char *cn_str = mpz_get_str(NULL, 10, cn);
    char *cr_str = mpz_get_str(NULL, 10, cr);

    // Output the results.
    std::printf("Process completed; took %.6f seconds.\n\n", time);
    std::printf("Permutations of set, cardinality %llu: %s\n", n, pa_str);
    std::printf("Total r-combinations of set for all r: %s\n", ca_str);
    std::printf("P(%llu, %llu) w/o repetition: %s\n", n, r, pn_str);
    std::printf("P(%llu, %llu) w/ repetition: %s\n", n, r, pr_str);
    std::printf("C(%llu, %llu) w/o repetition: %s\n", n, r, cn_str);
    std::printf("C(%llu, %llu) w/ repetition: %s\n", n, r, cr_str);

    mpz_clears(pa, pn, pr, ca, cn, cr, NULL);
}