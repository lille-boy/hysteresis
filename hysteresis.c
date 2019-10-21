/**************************************************************************************************
 * Example of a hysteresis
 * The hysteresis takes a percentage as an input.
 * It ouputs a level between 0 and 4.
 *************************************************************************************************/

/* Hysteresis diagram
 *
 *
 *   level
 *   ^
 *   |
 * 4_|. . . . . . . . . . . . . . . . . . .____________
 *   |                                     |  |
 *   |                                     v  ^
 *   |                                     |  |
 * 3_|. . . . . . . . . . . . . .__________|__|
 *   |                          |  |       .  .
 *   |                          v  ^       .  .
 *   |                          |  |       .  .
 * 2_|. . . . . . . . __________|__|       .  .
 *   |                |  |      .  .       .  .
 *   |                v  ^      .  .       .  .
 *   |                |  |      .  .       .  .
 * 1_|. . .___________|__|      .  .       .  .
 *   |     |  |       .  .      .  .       .  .
 *   |     v  ^       .  .      .  .       .  .
 *   |     |  |       .  .      .  .       .  .
 * 0_|_____|__|______________________________________|  percent
 *         |  |       |  |      |  |      |  |       |
 *        10  15     35  40    60  65    85  90     100
 *
 */

#include <stdio.h>
#include "hysteresis.h"

#define NB_THRESHOLDS   4

struct threshold {
    unsigned int low;
    unsigned int high;
    unsigned int level;
};

const struct threshold thresholds[NB_THRESHOLDS] = {
    {.low = 10, .high = 15, .level = 1},
    {.low = 35, .high = 40, .level = 2},
    {.low = 60, .high = 65, .level = 3},
    {.low = 85, .high = 90, .level = 4},
};

unsigned int hysteresis(unsigned int input_percent)
{
    static unsigned int discrete_level = 0;
    static unsigned int prev_input_precent = 0;

    if (DEBUG >= 2) {
        printf("input: %d, prev. input: %d, ", input_percent, prev_input_precent);
    }

    if (input_percent >= prev_input_precent) {
        for(int i = 0; i < NB_THRESHOLDS; i++) {
            if (input_percent >= thresholds[i].high) {
                discrete_level = thresholds[i].level;
            }
        }
    }
    else {
        for (int i = 0; i < NB_THRESHOLDS; i++) {
            if (input_percent <= thresholds[NB_THRESHOLDS-1-i].low) {
                discrete_level = thresholds[NB_THRESHOLDS-1-i].level - 1;
            }
        }
    }

    prev_input_precent = input_percent;

    if (DEBUG >= 2) {
        printf("level: %d\n", discrete_level);
    }

    return discrete_level;
 }
