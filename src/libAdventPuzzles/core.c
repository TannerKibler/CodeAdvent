#include "core.h"


void run_advent_day_puzzles(int day, int puzzle) {
	switch(day) {
		case 1:
			if (puzzle == 1)
				execute_day1_puzzle1();
			else if (puzzle == 2)
				execute_day1_puzzle2();
			break;
		case 2:
			if (puzzle == 1)
				execute_day2_puzzle1();
			else if (puzzle == 2)
				execute_day2_puzzle2();
			break;
		default:
			printf("\nDid not receive a valid day:puzzle combination!\n");
	}

}

void set_integer_value(char* strSource, int** intDest) {
	if (strSource == NULL)
		return;

	int swapInt;

	*intDest = malloc(sizeof(int)*strlen(strSource) + 4);
	if (*intDest == NULL) {
		// error allocating
		// handle this
		return;
	}

	printf("\nGot source string from input: %s\n----------------\n", strSource);

	swapInt = atoi(strSource);
	*intDest = &swapInt;
	//strcpy(*strDest, strSource);
}

void execute_day1_puzzle1() {};
void execute_day1_puzzle2() {};

void execute_day2_puzzle1() {
	char *file_buffer = NULL;

	register int i = 0;
	int action = 0, up = 0, right = 0, row_movement = 0, final_result_multiplied = 0, down = 0;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day2\0");
	while (file_buffer[i] != '\0') {
		if (i == 0 || file_buffer[i-1] == '\n') { // reading first char of new line or first line
			switch(file_buffer[i]) {
				case 'f':
					action = 1;
					break;
				case 'u':
					action = 2;
					break;
				case 'd':
					action = 3;
					break;
			}
		}
		else if (file_buffer[i-1] == ' ') {
			//reading number into from file
			row_movement = file_buffer[i] - '0';
		}

		if (action != 0 && row_movement != 0) {
			if (action == 1) 
				right = right + row_movement;
			else if (action == 3)
				down = down + row_movement;
			else if (action == 2)
				up = up + row_movement;

			action = 0;
			row_movement = 0;
		}
		i++;
	}

	final_result_multiplied = (down - up) * right;
	printf("Got final result: %d\n", final_result_multiplied);
};

void execute_day2_puzzle2() {
	char *file_buffer = NULL;

	register int i = 0;
	int action = 0, aim = 0, right = 0, depth = 0, row_movement = 0, final_result_multiplied = 0;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day2\0");
	while (file_buffer[i] != '\0') {
		if (i == 0 || file_buffer[i-1] == '\n') { // reading first char of new line or first line
			switch(file_buffer[i]) {
				case 'f':
					action = 1;
					break;
				case 'u':
					action = 2;
					break;
				case 'd':
					action = 3;
					break;
			}
		}
		else if (file_buffer[i-1] == ' ') {
			//reading number into from file
			row_movement = file_buffer[i] - '0';
		}

		if (action != 0 && row_movement != 0) {
			if (action == 1) {
				right = right + row_movement;
				depth = depth + (aim*row_movement);
			}
			else if (action == 3)
				aim = aim + row_movement;
			else if (action == 2)
				aim = aim - row_movement;

			action = 0;
			row_movement = 0;
		}
		i++;
	}

	final_result_multiplied = depth * right;
	printf("Got final result: %d\n", final_result_multiplied);
};

char* substring(char *str, int stIndex, int enIndex) {
	char *retString = NULL;
	int loopIn = 0;

	if (enIndex < stIndex)
		return NULL;

	if ((enIndex - stIndex) > 1)
		retString = malloc((sizeof(char)*(enIndex - stIndex) + 8));
	else
		retString = malloc(32);
	while(stIndex <= enIndex && str[stIndex] != '\0') {
		retString[loopIn] = str[stIndex];
		stIndex++;
		loopIn++;
	}

	retString[loopIn] = '\0';

	return retString;
}
