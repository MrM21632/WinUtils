/*
 * prime_test.cpp: Math Utility #6. Determine if the given integer is prime, then
 * find and output the next prime starting from the same integer.
 *
 * Version:     1.0.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/8/2017, 9:30pm
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
* mod_add(): Modular Addition, as defined for Unsigned 64-bit Integers. This
* ensures integer overflow is avoided.
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
* This ensures integer overflow is avoided.
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
* This ensures integer overflow is avoided.
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
*         uint64_t d - an odd integer > 1, such that n - 1 = d * 2^r for some
*                      integer r > 1.
* Output: true if n is (likely) prime, or false if n is composite.
*/
bool miller_rabin(uint64_t n, uint64_t d) {
	std::uniform_int_distribution<uint64_t> dist(2, n - 2);

	uint64_t a = dist(mt);          // Randomly select a from [2, n-2]
	uint64_t x = mod_pow(a, d, n);  // Let x = a^d mod n

	// Base Case: if a^d mod n is 1 or n-1, then we can already assume n is
	// prime, so we can return true.
	if (x == 1 || x == n - 1)
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
* next_prime(): Determines the next prime after a given starting point, n.
*
* Input:  uint64_t n - the starting point for the prime search.
* Output: The next prime number following n. Note that n itself can be prime.
*/
uint64_t next_prime(uint64_t n) {
	// This loop performs the following operations for i in [n + 1, inf):
	//     1. If is_prime(i), return i.
	//     2. Increment i.
	for (uint64_t i = n + 1; ; ++i) {
		if (is_prime(i, TEST_NUM))
			return i;
	}
}


int main(int argc, char **argv) {
	if (argc != 2) {
		std::printf("Usage: prime_test [n]\n");
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