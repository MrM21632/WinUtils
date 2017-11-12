/*
 * die_roll.cpp: Die Rolling utility. Generates a random number through the
 * following format: NdS(+/-)M, where
 *     - N is the number of dice being rolled
 *     - S is the number of sides per die. The following numbers are allowed:
 *       2, 3, 4, 5, 6, 7, 8, 10, 12, 20, 24, 30, % (100)
 *     - M is the modifier being applied (positive if + is added, negative if -
 *       is added).
 * This program also allows for more than one roll, if desired.
 *
 * Version:     1.1.0
 * License:     Public Domain
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 11/4/2017, 5:00pm
 */

#include <iostream>
#include <random>
#include <cstdlib>

/* Global Variables */
std::random_device rd;
std::mt19937 mt(rd());


int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "Usage: die_roll [total] [dice] [sides] [mod] [p/m]" << std::endl;
        std::cout << "\ttotal: Total rolls to make (> 0)" << std::endl;
        std::cout << "\tdice: Number of dice to roll (> 0)" << std::endl;
        std::cout << "\tsides: Sides per die (Supports any die side, including % for percentiles)" << std::endl;
        std::cout << "\tmod: Modifier to die roll (p=positive, m=negative)\n" << std::endl;
        std::cout << "Generates (total) random numbers in the range [dice + mod, (dice)(sides) + mod]." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Set up our variables
    int total = std::atoi(argv[1]);
    int dice = std::atoi(argv[2]);
    
    int mod = std::atoi(argv[4]);
    if (argv[5][0] == 'm')
        mod *= (-1);
    
    int min = dice + mod;
    if (min < 0)
        min = 1;  // Minimum result of 1
    
    int sides;
    if (argv[3][0] == '%')  // Percentiles
        sides = 100;
    else
        sides = std::atoi(argv[3]);
    
    int max = (dice * sides) + mod;
    if (max < 0)
        max = 1;  // Minimum (maximum?) of 1
    
    // Roll the dice
    std::uniform_int_distribution<int> dist(min, max);
    for (int i = 1; i <= total; ++i)
        std::cout << "Die Roll #" << i << ": " << dist(mt) << std::endl;
}