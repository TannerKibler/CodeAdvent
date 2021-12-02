#ifndef CORE_H
#define CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "file.h"

#ifdef CUSTOM_PATH_CAP
	#define MAX_PATH CUSTOM_PATH_CAP
#endif
#ifndef CUSTOM_PATH_CAP
	#define MAX_PATH 150
#endif

void run_advent_day_puzzles(int day, int puzzle);
void execute_day1_puzzle1();
void execute_day1_puzzle2();
void execute_day2_puzzle1();
void execute_day2_puzzle2();
void set_integer_value(char* strSource, int** intDest);
char* substring(char* str, int stIndex, int enIndex);

#ifdef __cplusplus
}
#endif

#endif
