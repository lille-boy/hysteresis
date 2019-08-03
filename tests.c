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
		if(DEBUG) {
			printf("%s: pass\n", test_name);
		}
	}
	else {
		fail++;
		if(DEBUG) {
			printf("%s: fail\n", test_name);
		}
	}
	
	executed++;
}

static void test_init(void)
{
	level = hysteresis(0);
	test_result("init", level, 0);
}

static void test_up(void) 
{
	level = hysteresis(14);
	test_result("level 0", level, 0);
	
	level = hysteresis(16);
	test_result("level 1", level, 1);
	
	level = hysteresis(41);
	test_result("level 2", level, 2);
	
	level = hysteresis(66);
	test_result("level 3", level, 3);
	
	level = hysteresis(91);
	test_result("level 4", level, 4);
}

static void test_down(void)
{
	level = hysteresis(90);
	test_result("level 4", level, 4);
	
	level = hysteresis(85);
	test_result("level 3", level, 3);
	
	level = hysteresis(60);
	test_result("level 2", level, 2);
	
	level = hysteresis(35);
	test_result("level 1", level, 1);
	
	level = hysteresis(10);
	test_result("level 0", level, 0);
}

static void test_edges(void)
{
	level = hysteresis(15);
	test_result("level 1", level, 1);
	
	level = hysteresis(40);
	test_result("level 2", level, 2);
	
	level = hysteresis(65);
	test_result("level 3", level, 3);
	
	level = hysteresis(90);
	test_result("level 4", level, 4);
	
	level = hysteresis(85);
	test_result("level 3", level, 3);
	
	level = hysteresis(60);
	test_result("level 2", level, 2);
	
	level = hysteresis(35);
	test_result("level 1", level, 1);
	
	level = hysteresis(10);
	test_result("level 0", level, 0);
}

static void test_jumps(void)
{
	level = hysteresis(16);
	test_result("level 1", level, 1);
	
	level = hysteresis(75);
	test_result("level 3", level, 3);
	
	level = hysteresis(100);
	test_result("level 4", level, 4);
	
	level = hysteresis(50);
	test_result("level 2", level, 2);
}

static void test_outofrange(void)
{
	level = hysteresis(101);
	test_result("level 4", level, 4);
}

void test_run_all(void) 
{
	test_init();
	test_up();
	test_down();
	test_edges();
	test_jumps();
	test_outofrange();
	
	printf("Tests Passed:   %d\n", pass);
	printf("Tests Failed:   %d\n", fail);
	printf("Tests Executed: %d\n", executed);
}