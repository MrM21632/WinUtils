/*
 * weasel.cpp: Evolutionary "Weasel" program.
 * Written by Joshua Morrison, 7-12-2017
 * Programming Practice
 * Last Edited: 7-12-2017, 1:45am
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>

/*** Global Variables ***/
std::string target;                                 // Our target string
std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";  // Available chars
int len;                                            // Target string's length
int chars_len = chars.length();                     // Number of available chars

// For the percentile roller
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> percentile(1, 100);
std::uniform_int_distribution<int> get_char(0, chars_len - 1);

/*** Function and Type Declarations ***/
int fitness(const std::string&);
std::string mutate(std::string, int);
bool less_fit(const std::string&, const std::string&);
bool isupper(char);


int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: weasel [target] [copies] [mutate]" << std::endl;
        std::cout << "\ttarget: Target string (UPPERCASE only)" << std::endl;
        std::cout << "\tcopies: Total children per generation" << std::endl;
        std::cout << "\tmutate: Chance to mutate (1 <= mutate <= 100)" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Set up our variables, including the required globals
    target = argv[1];
    len = target.length();
    int copies = std::atoi(argv[2]);
    int rate = std::atoi(argv[3]);

    // Check to see if the target has only the available characters; if not, exit
    for (int i = 0; i < len; ++i) {
        if (isupper(target[i]) || target[i] == ' ')
            continue;
        else {
            std::cout << "ERROR: Target string contains illegal character. Only the following chars are allowed:" << std::endl;
            std::cout << "\t" << chars << std::endl;
            return EXIT_FAILURE;
        }
    }
    
    std::string parent;
    for (int i = 0; i < len; ++i)
        parent += chars[get_char(mt)];
    int init_fit = fitness(parent);
    
    for (int f = init_fit, gen = 1; f < len; f = fitness(parent), ++gen) {
        std::cout << parent << ": " << f << " (Generation " << gen << ")" << std::endl;
        std::vector<std::string> children;
        children.reserve(copies + 1);
        children.push_back(parent);
        
        for (int i = 0; i < copies; ++i)
            children.push_back(mutate(parent, rate));
        
        parent = *std::max_element(children.begin(), children.end(), less_fit);
    }
    
    std::cout << "Final String: " << parent << std::endl;
}


/*** Function Definitions ***/

// Determines the "closeness" of the given string to the target.
int fitness(const std::string& s) {
    int score = 0;
    
    for (int i = 0; i < len; ++i) {
        if (s[i] == target[i])
            ++score;
    }
    
    return score;
}

// Mutate the string.
std::string mutate(std::string s, int m) {
    for (int i = 0; i < len; ++i) {
        int p = percentile(mt);
        if (p <= m)
            s[i] = chars[get_char(mt)];
    }
    
    return s;
}

// Comparator for std::max_element.
bool less_fit(const std::string& s1, const std::string& s2) {
    return fitness(s1) < fitness(s2);
}

// C-like boolean method to see if a character is uppercase only
bool isupper(char c) {
    return c >= 'A' && c <= 'Z';
}