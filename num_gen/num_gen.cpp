/*
 * num_gen.cpp: Number Generation Utility. Generates a list of integers within a
 *     given range (min to max).
 *
 * Written by Joshua Morrison, 9-15-2017
 * Last Edited: 9-15-2017, 8:30pm
 */

#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>

/*** Function and Type Declarations ***/
typedef long long int lli;
std::random_device rd;
std::mt19937 mt(rd());


int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: num_gen [total] [min] [max]" << std::endl;
        std::cout << "\ttotal: Total number of numbers to generate" << std::endl;
        std::cout << "\tmin: Minimum bound for generation" << std::endl;
        std::cout << "\tmax: Maximum bound for generation" << std::endl;
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
        fout << dist(mt) << std::endl;
    
    fout.close();
}