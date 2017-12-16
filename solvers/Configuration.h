/*
 * Configuration.h: Configuration interface definition and method declarations.
 * 
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/11/2017, 9:20pm
 */

#ifndef __GUARD__CONFIGURATION_H_
#define __GUARD__CONFIGURATION_H_

#include <vector>

/**
 * Configuration: Interface generalizing a configuration for the solvers.
 */
class Configuration {
    public:
        Configuration() {}
        virtual ~Configuration() {}
        virtual std::vector<Configuration*> get_successors() = 0;
        virtual bool is_valid() = 0;
        virtual bool is_solution() = 0;
}

#endif  // __GUARD__CONFIGURATION_H_