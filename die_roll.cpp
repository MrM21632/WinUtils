/*
 * die_roll.cpp: Die rolling utility. Generates a random number of the following
 * format: NdS(+/-)M.
 *     - N: number of dice being rolled.
 *     - S: number of sides per die; any number is allowed, and % can be used
 *          as a stand-in for 100.
 *     - M: modifier to apply to the roll (positive or negative).
 * This program also allows for multiple rolls (same format for all), if desired.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (GitHub: MrM21632)
 * Last Edited: 7/4/2018, 1:45pm
 */

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>


int main(int argc, char **argv) {
    if (argc != 5) {
        std::printf("Usage: die_roll total dice sides mod\n");
        std::printf("Generates random numbers in the range [dice + mod, (dice)(sides) + mod].\n\n");
        std::printf("total\t\tTotal rolls to make (> 0)\n");
        std::printf("dice\t\tNumber of dice to roll (> 0)\n");
        std::printf("sides\t\tSides per die (any positive number, or %%)\n");
        std::printf("mod\t\tModifier to die roll (positive or negative)\n");

        return EXIT_FAILURE;
    }

    // Setting up the variables
    int total = std::atoi(argv[1]);
    int dice = std::atoi(argv[2]);
    int mod = std::atoi(argv[4]);

    int min = dice + mod;
    if (min <= 0)
        min = 1;  // Guaranteed minimum result

    int sides;
    if (argv[3][0] == '%')  // Percentile
        sides = 100;
    else
        sides = std::atoi(argv[3]);

    int max = (dice * sides) + mod;
    if (max <= 0)
        max = 1;  // Guaranteed maximum(?) result


    // Roll the bones
    boost::random::random_device rd;
    boost::random::mt19937 mt(rd());
    boost::random::uniform_int_distribution<uint32_t> dist(min, max);

    for (int i = 1; i <= total; ++i)
        std::printf("Die Roll #%d: %u\n", i, dist(mt));
}
