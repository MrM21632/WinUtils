/*
 * num_gen.cpp: Number Generation Utility. Generates a list of integers within a
 *     given range (min to max).
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>

typedef long long int lli;
std::random_device rd;
std::mt19937 mt(rd());


int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: num_gen total min max\n";
        std::cout << "\ttotal: Total number of numbers to generate\n";
        std::cout << "\tmin: Minimum bound for generation\n";
        std::cout << "\tmax: Maximum bound for generation\n\n";
        std::cout << "Generate a list of (total) numbers from (min) to (max).\n";
        return EXIT_FAILURE;
    }
    
    // Set up the input file and our variables
    std::ofstream fout("numbers.txt");
    lli total = static_cast<lli>(std::atoi(argv[1]));
    lli min = static_cast<lli>(std::atoi(argv[2]));
    lli max = static_cast<lli>(std::atoi(argv[3]));
    std::uniform_int_distribution<lli> dist(min, max);
    
    // Generate numbers and write to our output file
    for (lli i = 0; i < total; ++i)
        fout << dist(mt) << "\n";
    
    fout.close();
}