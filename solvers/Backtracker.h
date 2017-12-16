/*
 * Backtracker.h: Backtracking class definition and method declarations.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/11/2017, 9:00pm
 */

#ifndef __GUARD__BACKTRACKER_H_
#define __GUARD__BACKTRACKER_H_

#include "Configuration.h"

/**
 * Backtracker: A class representation of the classic recursive backtracking
 * algorithm.
 */
class Backtracker {
    public:
        Backtracker();
        ~Backtracker();
        Configuration* solve(Configuration*);
}

#endif  // __GUARD__BACKTRACKER_H_