#ifndef HYSTERESIS_H

#define DEBUG 0

#define TABLE_LENGTH 4

typedef struct s_transition
{
	int lvl;
	unsigned int down;
	unsigned int up;
} t_transition;

unsigned int hysteresis(unsigned int new_percentage);

#endif
