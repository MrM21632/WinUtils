/*
 * die_roll.cpp: Die Rolling utility. Generates a random number of the following
 * format: NdS(+/-)M.
 *     - N is the number of dice being rolled.
 *     - S is the number of sides per die. Any number is allowed, including % as
 *       a stand-in for 100.
 *     - M is the modifier being applied (positive or negative).
 * This program also allows for more than one roll, if desired.
 *
 * Version:     1.2.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/09/2017, 10:10pm
 */

#include <iostream>
#include <random>
#include <cstdlib>

/* Global Variables */
std::random_device rd;
std::mt19937 mt(rd());


int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Usage: die_roll total dice sides mod\n";
        std::cout << "\ttotal: Total rolls to make (> 0)\n";
        std::cout << "\tdice: Number of dice to roll (> 0)\n";
        std::cout << "\tsides: Sides per die (Supports any die side, including % for percentiles)\n";
        std::cout << "\tmod: Modifier to die roll (positive or negative)\n\n";
        std::cout << "Generates (total) random numbers in the range [dice + mod, (dice)(sides) + mod].\n";
        return EXIT_FAILURE;
    }
    
    // Set up our variables
    int total = std::atoi(argv[1]);
    int dice = std::atoi(argv[2]);
    
    int mod = std::atoi(argv[4]);
    
    int min = dice + mod;
    if (min <= 0)
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
        std::cout << "Die Roll #" << i << ": " << dist(mt) << "\n";
}