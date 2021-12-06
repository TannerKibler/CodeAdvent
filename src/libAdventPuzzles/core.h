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
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#ifdef CUSTOM_PATH_CAP
	#define MAX_PATH CUSTOM_PATH_CAP
#endif
#ifndef CUSTOM_PATH_CAP
	#define MAX_PATH 150
#endif

typedef struct ADVENT_BIT_COMMON ADVENT_BIT_COMMON;
typedef struct ADVENT_BINGO_BOARD ADVENT_BINGO_BOARD;
typedef struct ADVENT_COORDINATE_LINE ADVENT_COORDINATE_LINE;
typedef struct ADVENT_COORDINATE_POINT ADVENT_COORDINATE_POINT;

void run_advent_day_puzzles(int day, int puzzle);
void execute_day1_puzzle1();
void execute_day1_puzzle2();
void execute_day2_puzzle1();
void execute_day2_puzzle2();
void execute_day3_puzzle1();
void execute_day3_puzzle2();
void execute_day4_puzzle1();
void execute_day4_puzzle2(); 
void execute_day5_puzzle1();
void execute_day5_puzzle2(); 
int get_oxygen_generator_rating();
int get_co2_scrubber();
int board_is_a_winner_winner_chicken_dinner(int board[5][5], int check_values[100]);
int sum_unused_numbers(int unused[25]);
ADVENT_COORDINATE_LINE* load_coordinate_lines(char* file_buffer, int skip_sloped_lines);
ADVENT_COORDINATE_POINT* get_my_line(ADVENT_COORDINATE_LINE *starting_points);
ADVENT_COORDINATE_POINT* load_all_points();
void set_integer_value(char* strSource, int** intDest);
char* substring(char* str, int stIndex, int enIndex);
ADVENT_BINGO_BOARD* load_bingo_boards(char* buffer, int length);


struct ADVENT_BIT_COMMON {
	char most_common;
	char least_common;
	struct ADVENT_BIT_COMMON *next;
	struct ADVENT_BIT_COMMON *first;
};

struct ADVENT_BINGO_BOARD {
	int unused_numbers[25];
	int board[5][5];
	int rows[5];
	int cols[5];
	int winner;
	struct ADVENT_BINGO_BOARD *next;
	struct ADVENT_BINGO_BOARD *first;
};

struct ADVENT_COORDINATE_POINT {
	int x;
	int y;
	ADVENT_COORDINATE_POINT *next;
	ADVENT_COORDINATE_POINT *first;
	int overlaps;
};

struct ADVENT_COORDINATE_LINE {
	int x1;
	int y1;
	int x2;
	int y2;
	int hits;
	int id;
	ADVENT_COORDINATE_POINT *points;
	struct ADVENT_COORDINATE_LINE *next;
	struct ADVENT_COORDINATE_LINE *last;
	struct ADVENT_COORDINATE_LINE *first;
};

#ifdef __cplusplus
}
#endif

#endif
