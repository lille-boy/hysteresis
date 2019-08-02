/*
 * Example of a hysteresis
 * The hysteresis takes a percentage as an input
 * It ouputs a level between 0 and 4
 */

#include <stdio.h>

#define THRES_LOW_POS   0
#define THRES_HIGH_POS  1
#define LEVEL_POS       2

#define NB_THRESHOLDS   4


enum levels {
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
};

const unsigned int thresholds[NB_THRESHOLDS][3] = {
    {10, 15, LEVEL_1},
    {35, 40, LEVEL_2},
    {60, 65, LEVEL_3},
    {85, 90, LEVEL_4}
};

unsigned int hysteresis(unsigned int input_percent) {
    
    unsigned int i = 0;
    unsigned int discrete_level;
    static unsigned int prev_input_precent = 0;
    
    if(input_percent >= prev_input_precent) {
        for(i = 0; i < NB_THRESHOLDS; i++) {
            if(input_percent >= thresholds[i][THRES_HIGH_POS]) {
                prev_input_precent = input_percent;
                discrete_level = thresholds[i][LEVEL_POS];
            }
        }
    }
    else {
        for(i = 0; i < NB_THRESHOLDS; i++) {
            if(input_percent <= thresholds[NB_THRESHOLDS-1-i][THRES_LOW_POS]) {
                prev_input_precent = input_percent;
                discrete_level = thresholds[NB_THRESHOLDS-1-i][LEVEL_POS] - 1;
            }
        }
    }

    return discrete_level;
}
