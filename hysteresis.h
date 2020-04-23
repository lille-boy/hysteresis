#ifndef HYSTERESIS_H
#define HYSTERESIS_H

#define DEBUG 1

/******************************************************************************
 * Function hysteresis:
 * - Translates a percentage into a level
 * - The output "sticks" to its level around defined values to avoid toggling
 * - For example, output could represent the 4 speed levels of a fan, according
 *   to a temperature input.
 *
 * Input: percentage between 0 and 100.
 * Output: level between 0 and 4.
 *****************************************************************************/
unsigned int hysteresis(unsigned int input_percent);

#endif /* HYSTERESIS_H */
