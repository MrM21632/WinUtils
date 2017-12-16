/*
 * Backtracker.cpp: Backtracking class method definitions.
 * 
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/11/2017, 9:20pm
 */

#include <iostream>
#include "Backtracker.h"


/**
 * Backtracker(): Class constructor.
 */
Backtracker::Backtracker() {
    std::cout << "Backtracker constructer called.\n";
}

/**
 * ~Backtracker(): Class destructor.
 */
Backtracker::~Backtracker() {
    std::cout << "Backtracker destructor called\n";
}

/**
 * solve(): Attempts to find a solution from the given starting Configuration.
 * If one is found, it is returned.
 * 
 * Input:  Configuration* c - the starting configuration.
 * Output: Either a valid solution of the problem, or nullptr (i.e., no
 *         solution).
 */
Configuration* Backtracker::solve(Configuration* c) {
    if (c->is_solution()) {
        std::cout << "Solution found.\n";
        return c;
    }
    else {
        std::vector<Configuration*> children = c->get_successors();
        for (Configuration* child : children) {
            if (child->is_valid()) {
                std::cout << "Valid successor configuration.\n";
                Configuration* sol = this->solve(child);
                if (sol != nullptr)
                    return sol;
            }
            else
                std::cout << "Invalid successor configuration.\n";
        }
        // Implicit backtracking happens at this point
    }
    
    // No solution found, return a null reference
    return nullptr;
}