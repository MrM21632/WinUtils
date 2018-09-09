/*
 * num_gen.cpp: Number generation utility. Generates a list of integers within a
 * given range (min to max).
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (GitHub: MrM21632)
 * Last Edited: 7/4/2018, 4:00pm
 */

#include <fstream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>


int main(int argc, char **argv) {
    if (argc != 4) {
        std::printf("Usage: num_gen total min max\n");
        std::printf("Generates a list of numbers in the range [min, max].\n\n");
        std::printf("total\t\tNumber of numbers to generate\n");
        std::printf("min\t\tMinimum bound for number generation\n");
        std::printf("max\t\tMaximum bound for number generation\n\n");
        std::printf("NOTE: Bounds must be within (-2^63, 2^63).\n");

        return EXIT_FAILURE;
    }

    char *end;
    uint64_t total = std::strtoull(argv[1], &end, 10);
    int64_t min = std::strtoll(argv[2], &end, 10);
    int64_t max = std::strtoll(argv[3], &end, 10);
    std::ofstream numbers_file("numbers.txt");

    boost::random::random_device rd;
    boost::random::mt19937 mt(rd());
    boost::random::uniform_int_distribution<int64_t> dist(min, max);

    for (uint64_t i = 0; i < total; ++i)
        numbers_file << dist(mt) << "\n";

    numbers_file.close();
    std::printf("Number generation complete.\n");
}
