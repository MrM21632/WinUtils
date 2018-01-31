/*
 * weasel.cpp: Weasel Algorithm. Simulates Dawkins' "Weasel Algorithm." Given a
 * target string, a number of copies to make each "generation," and a chance for
 * a character to "mutate," iterate through as many "generations" as required
 * until a copy of the target string is found. This version of the algorithm
 * allows the user to select the target, the number of copies per generation,
 * and the chance for each character to mutate.
 *
 * Version:     1.0.0-rc1
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
 * fitness(): Determine how "fit" the given string is - that is, how close it is
 * to the target string.
 *
 * Input:  const std::string& s - the string to test.
 * Output: The fitness score of s.
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
 * mutate(): Generates a mutated clone of the given string using the given
 * mutation chance.
 *
 * Input:  std::string s - the string to clone.
 *         int m - the chance for a single character to mutate.
 * Output: A (possibly mutated) clone of s.
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
 * less_fit(): Comparison method for std::max_element. Determines if s1 is less
 * fit than s2.
 *
 * Input:  std::string &s1, &s2 - the strings to compare.
 * Output: true if s1 is less fit, false otherwise.
 */
bool less_fit(const std::string &s1, const std::string &s2) {
    return fitness(s1) < fitness(s2);
}

/**
 * isupper(): C-like comparison method to see if a character is uppercase only.
 *
 * Input:  char c - the character to check.
 * Output: true if c is uppercase, false otherwise.
 */
bool isupper(char c) {
    return c >= 'A' && c <= 'Z';
}


int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: weasel target copies mutate\n";
        std::cout << "\ttarget: Target string (UPPERCASE only)\n";
        std::cout << "\tcopies: Total children per generation\n";
        std::cout << "\tmutate: Chance to mutate (1 <= mutate <= 100)\n\n";
        std::cout << "Simulates Dawkins' famed \"Weasel Algorithm.\"\n";
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