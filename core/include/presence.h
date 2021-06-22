#ifndef PRESENCE_H
#define PRESENCE_H

#include <stdbool.h>

/**
 * This module contains the tools to manage the presence of an object, which
 * can be an edge or a vertex.
 */

typedef struct presence_function
{
    /**
     * This structure abstarct the presence function.
     * 
     * It can be periodic presence function, which has a known presence
     * pattern. In this case, the variable "length" represents the length
     * of the pattern that is greater than 0, and the variable presence
     * points to an array of unsigned char of length/8 + 1 elements.
     * 
     * The presence function can also reprensents a recurrent presence
     * function. In this case, the variable "length" must be at 0 and the
     * presence pointer is a function that takes an integer representing a
     * time step as input and returns a boolean.
     */

    unsigned long length;
    void *presence;
} presence_function;

/**
 * Return boolean meaning if the object with the presence function pointer
 * "p" is present at the time "t".
 */
bool is_present(presence_function *p, unsigned long t);

/**
 * It takes a string pattern "str_pattern" composed of 0 and 1 meaning if
 * the object is present or not, and formats it as an array of unsigned
 * char of strlen(str_pattern)/8 + 1 elements where formatted_pattern
 * points on the first element. It returns "true" if the procedure succeeds,
 * or "false" otherwise.
 */
bool str_to_periodic_pattern(char str_pattern[],
                             unsigned char *formatted_pattern);

#endif