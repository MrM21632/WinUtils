/*
 * fact.cpp: Math Utility #4. Compute the following values for a given integer:
 *     1. The regular factorial, n!
 *     2. The double factorial, n!!
 *     3. The primorial, n#
 *     4. The derangement or subfactorial, !n
 *
 * Version:     1.0.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/5/2017, 10:30pm
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mpir.h>


/**
 * derange(): Compute the derangement of n, !n.
 *
 * Input:  mpz_t res - arbitrary-precision integer to store the calculation.
 *         mpir_ui n - the number to compute the derangement of.
 * Output: N/A. The calculation is stored in res.
 */
void derange(mpz_t res, mpir_ui n) {
	// Base Cases: !0 = 1, !1 = 0.
	if (n == 0) {
		mpz_set_ui(res, 1);
		return;
	}
	if (n == 1) {
		mpz_set_ui(res, 0);
		return;
	}

	// Setup Euler's constant and 1/2 for use.
	mpf_t e_mpf; mpf_init(e_mpf); mpf_set_d(e_mpf, std::exp(1.0));
	mpf_t half; mpf_init(half); mpf_set_d(half, 0.5);

	// Calculate n!, then turn it into a float.
	mpz_fac_ui(res, n);
	mpf_t fac_f; mpf_init(fac_f); mpf_set_z(fac_f, res);

	// Set fac_f = (fac_f / e_mpf) + half.
	mpf_div(fac_f, fac_f, e_mpf);
	mpf_add(fac_f, fac_f, half);

	// Floor fac_f, and set res to the result.
	mpf_floor(fac_f, fac_f);
	mpz_set_f(res, fac_f);
	mpf_clears(fac_f, half, e_mpf, NULL);
}


int main(int argc, char **argv) {
	if (argc != 2) {
		std::printf("Usage: fact [n]\n");
		std::printf("\tn: The number to perform the calculations for.\n\n");
		std::printf("Compute various values for a given number, n:\n");
		std::printf("\t- Regular factorial, n!\n");
		std::printf("\t- Double factorial, n!!\n");
		std::printf("\t- Derangement, !n\n");
		std::printf("\t- Primorial, n# (product of all primes below n)\n");
		std::exit(EXIT_FAILURE);
	}

	// Get the value n from argv
	char *e;
	mpir_ui n = static_cast<mpir_ui>(std::strtoull(argv[1], &e, 10));

	// Setup the arbitrary-precision integers.
	//     1. fact_n: n!
	//     2. doub_n: n!!
	//     3. prim_n: n#
	//     4. derg_n: !n
	mpz_t fact_n, doub_n, prim_n, derg_n;
	mpz_inits(fact_n, doub_n, prim_n, derg_n, NULL);

	// Perform the calculations.
	clock_t start = std::clock();
	mpz_fac_ui(fact_n, n);
	mpz_2fac_ui(doub_n, n);
	mpz_primorial_ui(prim_n, n);
	derange(derg_n, n);
	clock_t end = std::clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	// Convert the calculations to strings, for ease of output.
	char *fact_str = mpz_get_str(NULL, 10, fact_n);
	char *doub_str = mpz_get_str(NULL, 10, doub_n);
	char *prim_str = mpz_get_str(NULL, 10, prim_n);
	char *derg_str = mpz_get_str(NULL, 10, derg_n);

	// Output the results.
	std::printf("Process completed; took %.6f seconds.\n\n", time);
	std::printf("%llu! = %s\n", n, fact_str);
	std::printf("%llu!! = %s\n", n, doub_str);
	std::printf("%llu# = %s\n", n, prim_str);
	std::printf("!%llu = %s\n", n, derg_str);

	mpz_clears(fact_n, doub_n, prim_n, derg_n, NULL);
}