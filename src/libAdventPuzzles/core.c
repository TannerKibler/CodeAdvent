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
		case 3:
			if (puzzle == 1)
				execute_day3_puzzle1();
			else if (puzzle == 2)
				execute_day3_puzzle2();
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

void execute_day3_puzzle1() {
	char *file_buffer = NULL, *gamma = NULL, *epsilon = NULL;
	ADVENT_BIT_COMMON *first_bit = NULL, *current = NULL;
	int index_to_read = 0, count_1 = 0, count_0 = 0, gamma_final = 0, epsilon_final = 0;
	register int i = 0;

	// magic number is 12 bits per line plus one new line char
	int index_skips = 13;

	gamma = malloc(sizeof(char)*13);
	epsilon = malloc(sizeof(char)*13);

	gamma[0] = '\0';
	epsilon[0] = '\0';

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day3\0");
	while (file_buffer[i] != '\0' && index_to_read < 12) {
		if (i == 0 && index_to_read == 0) {
			first_bit = malloc(sizeof(ADVENT_BIT_COMMON));
			if (!first_bit)
				return;

			current = first_bit;
			current->next = NULL;
			current->first = malloc(sizeof(ADVENT_BIT_COMMON));
			if (!current->first)
				return;

			current->first = first_bit;
		}

		if (file_buffer[i] == '1')
			count_1++;
		else
			count_0++;

		i = i + index_skips;

		// read all indexes of file and have skipped past end of file; I know there may be garbage here but I sure hope not
		if (!file_buffer[i]) {
			index_to_read++;
			i = index_to_read;

			if (count_1 > count_0) {
				current->most_common = '1';
				current->least_common = '0';
			}
			else {
				current->most_common = '0';
				current->least_common = '1';
			}

			count_1 = 0;
			count_0 = 0;

			current->next = malloc(sizeof(ADVENT_BIT_COMMON));
			if (!current->next)
				return;

			current->next->first = malloc(sizeof(ADVENT_BIT_COMMON));
			if (!current->first)
				return;

			current->next->first = current->first;

			current = current->next;
			current->next = NULL;
		}
	}

	current = current->first;
	int struct_index = 0;
	while (current) {
		gamma[struct_index] = current->most_common;
		epsilon[struct_index] = current->least_common;
		current = current->next;

		struct_index++;
	}

	gamma[struct_index-1] = '\0';
	epsilon[struct_index-1] = '\0';

	printf("Got gamma bit: %s\n", gamma);
	printf("Got epsilon bit: %s\n", epsilon);

	gamma_final = (int) strtol(gamma, NULL, 2);
	epsilon_final = (int) strtol(epsilon, NULL, 2);

	printf("Got gamma int: %d\n", gamma_final);
	printf("Got epsilon int: %d\n", epsilon_final);
	printf("Got final answer: %d\n", (gamma_final*epsilon_final));
};

int check_index_against_target(char target, char value) {
	if (!target)
		return 0;

	if (target == value)
		return 1;

	return 0;
};

int get_co2_scrubber() {
	char *file_buffer = NULL;
	int index_to_read = 0, count_1 = 0, count_0 = 0, buffer_length = 0, final_rating = 0, last_good_index = 0;
	register int i = 0;

	char *value = NULL, *key_string = NULL;
	value = malloc(sizeof(char)*13);
	value[0] = '\0';
	key_string = malloc(sizeof(char)*13);
	key_string[0] = '\0';

	// magic number is 12 bits per line plus one new line char
	int index_skips = 13;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day3\0");
	buffer_length = strlen(file_buffer);
	while (i <= buffer_length && index_to_read < 12) {
		// if I have initialized a key, start checking it
		if (key_string[0] != '\0') {
			value = substring(file_buffer, i - index_to_read, i-1);
			if (strcmp(key_string,value) != 0) {
				// if I did not match, but I am still within file, keep going
				if ((i + index_skips) <= buffer_length) {
					i = i + index_skips;
				}
				else {
					// if I did not match and I am out of file, BUT only had one row match then that row is my row 
					if ((count_1 + count_0) == 1) {
						// go back to that last good match and grab the rest of the row
						i = last_good_index;
						while(i <= buffer_length && file_buffer[i] != '\n') {
							key_string[index_to_read] = file_buffer[i];
							i++;
							index_to_read++;
						}
						key_string[index_to_read+1] = '\0';
						break;
					}
					if (count_1 > count_0) {
						key_string[index_to_read] = '0';
						key_string[index_to_read+1] = '\0';
					}
					else if (count_0 > count_1) {
						key_string[index_to_read] = '1';
						key_string[index_to_read+1] = '\0';
					}
					else {
						key_string[index_to_read] = '0';
						key_string[index_to_read+1] = '\0';
					}

					index_to_read++;
					i = index_to_read;

					count_1 = 0;
					count_0 = 0;
				}
			}
			else {
				last_good_index = i;
				if (file_buffer[i] == '1')
					count_1++;
				else
					count_0++;

				i = i + index_skips;
			}
		}
		else {
			if (file_buffer[i] == '1')
				count_1++;
			else
				count_0++;

			i = i + index_skips; 
		}

		if (i > buffer_length) {
			if (count_1 > count_0) {
				key_string[index_to_read] = '0';
				key_string[index_to_read+1] = '\0';
			}
			else if (count_0 > count_1) {
				key_string[index_to_read] = '1';
				key_string[index_to_read+1] = '\0';
			}
			else {
				key_string[index_to_read] = '0';
				key_string[index_to_read+1] = '\0';
			}

			index_to_read++;
			i = index_to_read;

			count_1 = 0;
			count_0 = 0;
		}
	}

	printf("Got final key string: %s\n", key_string);
	final_rating = (int) strtol(key_string, NULL, 2);
	printf("Got final co2 scrubber: %d\n", final_rating);

	return final_rating;

}

int get_oxygen_generator_rating() {
	char *file_buffer = NULL;
	int index_to_read = 0, count_1 = 0, count_0 = 0, buffer_length = 0, final_rating = 0;
	register int i = 0;

	char *value = NULL, *key_string = NULL;
	value = malloc(sizeof(char)*13);
	value[0] = '\0';
	key_string = malloc(sizeof(char)*13);
	key_string[0] = '\0';

	// magic number is 12 bits per line plus one new line char
	int index_skips = 13;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day3\0");
	buffer_length = strlen(file_buffer);
	while (i <= buffer_length && index_to_read < 12) {
		// Have initialized key string, start checking against it
		if (key_string[0] != '\0') {
			value = substring(file_buffer, i - index_to_read, i-1);
			if (strcmp(key_string,value) != 0) {
				// if no match but I still have file to read, skip to next line
				if ((i + index_skips) <= buffer_length) {
					i = i + index_skips;
				}
				else {
					// if no match and I am OUT of file, push to key and go back to top of file
					if (count_1 > count_0) {
						key_string[index_to_read] = '1';
						key_string[index_to_read+1] = '\0';
					}
					else if (count_0 > count_1) {
						key_string[index_to_read] = '0';
						key_string[index_to_read+1] = '\0';
					}
					else {
						key_string[index_to_read] = '1';
						key_string[index_to_read+1] = '\0';
					}

					index_to_read++;
					i = index_to_read;

					count_1 = 0;
					count_0 = 0;
				}
			}
			else {
				// Had key match, keep on trucking
				if (file_buffer[i] == '1')
					count_1++;
				else
					count_0++;

				i = i + index_skips;
			}
		}
		else {
			// This is the count for the first index in key
			if (file_buffer[i] == '1')
				count_1++;
			else
				count_0++;

			i = i + index_skips; 
		}

		// if I have gone past the edge of file, push to key and circle back
		if (i > buffer_length) {
			if (count_1 > count_0) {
				key_string[index_to_read] = '1';
				key_string[index_to_read+1] = '\0';
			}
			else if (count_0 > count_1) {
				key_string[index_to_read] = '0';
				key_string[index_to_read+1] = '\0';
			}
			else {
				key_string[index_to_read] = '1';
				key_string[index_to_read+1] = '\0';
			}

			index_to_read++;
			i = index_to_read;

			count_1 = 0;
			count_0 = 0;
		}
	}

	printf("Got final key string: %s\n", key_string);
	final_rating = (int) strtol(key_string, NULL, 2);
	printf("Got final o2 value: %d\n", final_rating);

	return final_rating;
}

void execute_day3_puzzle2() {
	int o2_rating = 0, co2_scrubber = 0;
	o2_rating = get_oxygen_generator_rating();
	co2_scrubber = get_co2_scrubber();

	printf("Final answer: %d\n", o2_rating*co2_scrubber);
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
