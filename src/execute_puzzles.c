#include <stdlib.h>
#include <unistd.h>
#include "libAdventPuzzles/config.h"
#include "libAdventPuzzles/core.h"
#include <getopt.h>
#include <stdio.h>

int main (int argc, char **argv){
	int opt;
	//int *day = NULL, *puzzle = NULL;
	int day;
	int puzzle;
	while ((opt = getopt(argc, argv, "gd:p:")) != -1) {
		switch (opt) {
			case 'd':
				printf("Calling Set Integer Value with value: %s\n", optarg);
				//set_integer_value(optarg, &day);
				day = atoi(optarg);
				break;
			case 'p':
				printf("Calling Set Integer Value with value: %s\n", optarg);
				puzzle = atoi(optarg);
				break;
			case 'g':
				printf("\nRunning puzzles!\n---------------------\n");
				printf("\nExecuting Day %d!\n--------------------\n", day);
				printf("\nExecuting Puzzle %d!\n--------------------\n", puzzle);
				run_advent_day_puzzles(day, puzzle);
				break;
		}
	}
}
