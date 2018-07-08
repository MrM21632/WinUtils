/*
 * weasel.cpp: Weasel Algorithm. Simulates Dawkins' "Weasel Algorithm." Given a
 * target string, a number of copies to make each "generation," and a chance for
 * a character to "mutate," iterate through as many "generations" as required
 * until a copy of the target string is found.
 * This version of the algorithm allows the user to select the target, the number
 * of copies per generation, and the chance for each character to mutate.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>


// Global variables
std::string target;                                 // Our target string
std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";  // Available chars
int len;                                            // Target string's length
int chars_len = chars.length();                     // Number of available chars

// For the percentile roller
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> percentile(1, 100);
std::uniform_int_distribution<int> get_char(0, chars_len - 1);


/**
 *  @brief Fitness Calculator
 *  
 *  @param [in] s String to observe
 *  @return The string's fitness score.
 *  
 *  @details Determines the fitness of a given string ("copy") by comparing it
 *           character-by-character to the target.
 */
int fitness(const std::string &s) {
    int score = 0;
    
    for (int i = 0; i < len; ++i) {
        if (s[i] == target[i])
            ++score;
    }
    
    return score;
}

/**
 *  @brief Mutation Method
 *  
 *  @param [in] s String to (possibly) mutate
 *  @param [in] m Chance for mutation per character
 *  @return A mutated copy of the string.
 *  
 *  @details Generates a copy of the given string, while simultaneously testing
 *           each character to see if it mutates.
 */
std::string mutate(std::string s, int m) {
    for (int i = 0; i < len; ++i) {
        int p = percentile(mt);
        if (p <= m)
            s[i] = chars[get_char(mt)];
    }
    
    return s;
}

/**
 *  @brief Comparison Method for std::max_element
 *  
 *  @param [in] s1 Operand
 *  @param [in] s2 Operand
 *  @return true if s1 is less fit than s2, false otherwise.
 *  
 *  @details Determines whether the fitness of the first string is less than
 *           that of the second string. This is used by std::max_element in
 *           the main element.
 */
bool less_fit(const std::string &s1, const std::string &s2) {
    return fitness(s1) < fitness(s2);
}

/**
 *  @brief C-like Comparison Method for Uppercase Characters
 *  
 *  @param [in] c Character to check
 *  @return true if c is uppercase, false otherwise.
 *  
 *  @details Determines if a given character is strictly uppercase.
 */
bool isupper(char c) {
    return c >= 'A' && c <= 'Z';
}


int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: weasel target copies mutate\n";
        std::cout << "Simulates Dawkins' famed \"Weasel Algorithm.\"\n\n";
        std::cout << "target\t\tTarget string (UPPERCASE and SPACE only)\n";
        std::cout << "copies\t\tTotal children per generation\n";
        std::cout << "mutate\t\tChance to mutate (1 <= mutate <= 100)\n";
        return EXIT_FAILURE;
    }
    
    // Set up our variables, including the required globals
    target = argv[1];
    len = target.length();
    int copies = std::atoi(argv[2]);
    int rate = std::atoi(argv[3]);

    // Check to see if the target has only the available characters. If not,
    // then exit with an error message.
    for (int i = 0; i < len; ++i) {
        if (isupper(target[i]) || target[i] == ' ')
            continue;
        else {
            std::cout << "Error: Target string contains illegal character. The following chars are allowed:";
            std::cout << chars << "\n";
            return EXIT_FAILURE;
        }
    }
    
    std::string parent;
    for (int i = 0; i < len; ++i)
        parent += chars[get_char(mt)];
    int init_fit = fitness(parent);
    
    for (int f = init_fit, gen = 1; f < len; f = fitness(parent), ++gen) {
        std::cout << parent << ": " << f << " (Generation " << gen << ")\n";
        std::vector<std::string> children;
        children.reserve(copies + 1);
        children.push_back(parent);
        
        for (int i = 0; i < copies; ++i)
            children.push_back(mutate(parent, rate));
        
        parent = *std::max_element(children.begin(), children.end(), less_fit);
    }
    
    std::cout << "Final String: " << parent << "\n";
}
