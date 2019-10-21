#include <stdio.h>
#include "hysteresis.h"

unsigned int level;
unsigned int pass = 0;
unsigned int fail = 0;
unsigned int executed = 0;

static void test_result(const char *test_name, unsigned int level, unsigned int expected)
{
	if(level == expected) {
		pass++;
		if(DEBUG >= 2) {
			printf("%s: pass\n", test_name);
		}
	}
	else {
		fail++;
		if(DEBUG >= 1) {
			printf("%s: fail - ", test_name);
            printf("returned level: %d, expected: %d.\n", level, expected);
		}
	}

	executed++;
}

static void test_init(void)
{
	level = hysteresis(0);
	test_result("init = 0", level, 0);
}

static void test_up(void)
{
	level = hysteresis(14);
	test_result("up from 0 to 14", level, 0);
	
	level = hysteresis(16);
	test_result("up from 14 to 16", level, 1);
	
	level = hysteresis(41);
	test_result("up from 16 to 41", level, 2);
	
	level = hysteresis(66);
	test_result("up from 41 to 66", level, 3);
	
	level = hysteresis(91);
	test_result("up from 66 to 91", level, 4);
}

static void test_down(void)
{
	level = hysteresis(86);
	test_result("down from 91 to 86", level, 4);
	
	level = hysteresis(84);
	test_result("down from 86 to 84", level, 3);
	
	level = hysteresis(59);
	test_result("down from 84 to 59", level, 2);
	
	level = hysteresis(34);
	test_result("down from 59 to 34", level, 1);
	
	level = hysteresis(9);
	test_result("down from 34 to 9", level, 0);
}

static void test_thresholds(void)
{
	level = hysteresis(15);
	test_result("threshold 15", level, 1);
	
	level = hysteresis(40);
	test_result("threshold 40", level, 2);
	
	level = hysteresis(65);
	test_result("threshold 65", level, 3);
	
	level = hysteresis(90);
	test_result("threshold 90", level, 4);
	
	level = hysteresis(85);
	test_result("threshold 85", level, 3);
	
	level = hysteresis(60);
	test_result("threshold 60", level, 2);
	
	level = hysteresis(35);
	test_result("threshold 35", level, 1);
    
    level = hysteresis(10);
	test_result("threshold 10", level, 0);
}

static void test_same_level(void)
{
	level = hysteresis(0);
	test_result("set level 0", level, 0);
	level = hysteresis(14);
	test_result("same level from 0 to 14", level, 0);

	level = hysteresis(16);
	test_result("set level 1", level, 1);
	level = hysteresis(39);
	test_result("same level from 16 to 39", level, 1);

	level = hysteresis(41);
	test_result("set level 2", level, 2);
	level = hysteresis(64);
	test_result("same level from 41 to 64", level, 2);

	level = hysteresis(66);
	test_result("set level 3", level, 3);
	level = hysteresis(89);
	test_result("same level from 66 to 89", level, 3);

	level = hysteresis(91);
	test_result("set level 4", level, 4);
	level = hysteresis(100);
	test_result("same level from 91 to 100", level, 4);
}


static void test_jumps(void)
{
    level = hysteresis(16); /* go to level 1 */
    level = hysteresis(75);
	test_result("jump from 16 to 75", level, 3);
    
    level = hysteresis(5);
	test_result("jump from 75 to 5", level, 0);
    
    level = hysteresis(100);
    test_result("jump from 5 to 100", level, 4);
    
    level = hysteresis(50);
	test_result("jump from 100 to 50", level, 2);
    
	level = hysteresis(91);
	test_result("jump from 50 to 91", level, 4);	
    
    level = hysteresis(25);
	test_result("jump from 91 to 25", level, 1);
}

void test_run_all(void)
{
	test_init();
	test_up();
	test_down();
	test_thresholds();
	test_same_level();
	test_jumps();

	printf("Tests Passed:   %d\n", pass);
	printf("Tests Failed:   %d\n", fail);
	printf("Tests Executed: %d\n", executed);
}
