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
		case 4:
			if (puzzle == 1)
				execute_day4_puzzle1();
			else if (puzzle == 2)
				execute_day4_puzzle2();
			break;
		case 5:
			if (puzzle == 1)
				execute_day5_puzzle1();
			else if (puzzle == 2)
				execute_day5_puzzle2();
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
	ADVENT_BIT_COMMON *first_bit = NULL, *current = NULL, *garbage_bit = NULL;
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
		garbage_bit = current;
		gamma[struct_index] = current->most_common;
		epsilon[struct_index] = current->least_common;
		current = current->next;
		free(garbage_bit);

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

ADVENT_BINGO_BOARD* load_bingo_boards(char* buffer, int buffer_length) {
	if (buffer == NULL || buffer[0] == '\0')
		return NULL;

	ADVENT_BINGO_BOARD *first = NULL, *current = NULL;
	register int i = 0, reading_value = 0, column_read = 0, row_read = 0, read_number = 0, value_int = 0;

	int read_first_line = 0, init_index = 0;
	char* value;
	value = malloc(sizeof(char)*3);
	if (!value)
		return NULL;

	value[0] = '\0';
	first = malloc(sizeof(ADVENT_BINGO_BOARD));
	if (!first)
		return NULL;

	current = first;
	current->next = NULL;
	//current->first = NULL;
	current->winner = 0;
	//current->first = malloc(sizeof(ADVENT_BINGO_BOARD));
	//if (!current->first)
	//	return NULL;

	//current->first = first;
	while (i <= buffer_length) {
		if (read_first_line == 0) {
			if (buffer[i] == '\n') {
				i++;
				read_first_line = 1;
			}
		}
		else {
			if (buffer[i] == '\n') {
				i++;
				continue;
			}

			if (read_number >= 25) {
				if (buffer[i+1] == '\0') {
					i++;
					current->next = NULL;
					continue;
				}
				read_number = 0;
				row_read = 0;
				column_read = 0;
				reading_value = 0;
				//printf("Starting new Board!\n");
				for (init_index = 0; init_index < 5; init_index++)
					current->rows[init_index] = 0;

				for (init_index = 0; init_index < 5; init_index++)
					current->cols[init_index] = 0;

				current->next = malloc(sizeof(ADVENT_BINGO_BOARD));
				if (!current->next)
					return NULL;

				current = current->next;
				current->winner = 0;
				current->next = NULL;
				//current->first = first;

				//i++;
				continue;
			}
			if (reading_value == 0) {
				if (buffer[i+1] != ' ') {
					reading_value = 1;
					value[0] = buffer[i];
				}
			}
			else {
				value[1] = buffer[i];
				value[2] = '\0';
				value_int = strtol(value, NULL, 10);
				current->unused_numbers[read_number] = value_int;
				current->board[row_read][column_read] = value_int;
				read_number++;
				if (column_read == 4)
					row_read++;
				if (column_read < 4)
					column_read++;
				else
					column_read = 0;
				i++;
				reading_value = 0;
			}
		}
		i++;
	}

	return first;
}

void execute_day4_puzzle1() {
	char *file_buffer = NULL,*value = NULL;
	register int i = 0;
	int check_values[100];
	int value_iterator = 0, sum_unused = 0, final_score = 0, buffer_length = 0;

	ADVENT_BINGO_BOARD *first = NULL, *current = NULL, *garbage_board = NULL;

	value = malloc(sizeof(char)*3);
	if (!value)
		return;

	value[0] = '\0';

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day4\0");
	buffer_length = strlen(file_buffer);
	first = load_bingo_boards(file_buffer, buffer_length);
	while (i <= 290) {
		if (i == 0) {
			value[0] = file_buffer[i];
			value[1] = file_buffer[i+1];
			value[2] = '\0';
			check_values[value_iterator] = strtol(value, NULL, 10);
			value_iterator++;
			i = i + 3;
			continue;
		}
		if (file_buffer[i-1] == ',' || file_buffer[i+1] == ',') {
			if (file_buffer[i-1] == ',') 
				value[0] = file_buffer[i];	

			if (file_buffer[i+1] != ',') {
				value[1] = file_buffer[i+1];
				value[2] = '\0';
				i = i + 3;
			}
			else {
				value[1] = '\0';
				i = i + 2;
			}

			check_values[value_iterator] = strtol(value, NULL, 10);
			value_iterator++;
			continue;
		}
		i++;
	}

	if (!first) {
		printf("Failed to load bingo boards!\n");
		return;
	}	

	register int row = 0, col = 0;
	int unused_iterator = 0;
	value_iterator = 0;
	while (value_iterator < 101) {
		current = first;
		while (current) {
			while (row < 5) {
				while (col < 5) {
					if (current->board[row][col] == check_values[value_iterator]) {
						current->rows[row]++;
						current->cols[col]++;

						for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) {
							if (current->unused_numbers[unused_iterator] == check_values[value_iterator]) {
								current->unused_numbers[unused_iterator] = 0;
							}
						}

						if (current->rows[row] == 5) {
							// process winner
							for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) 
								sum_unused += current->unused_numbers[unused_iterator];

							printf("Sum of unused indexes: %d\n", sum_unused);
							printf("Winning number: %d\n", check_values[value_iterator]);
							final_score = sum_unused*check_values[value_iterator];
							printf("Huzzah, a board won! Final score: %d\n", final_score);
							return;
						}

						if (current->cols[col] == 5) {
							// process winner
							for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) 
								sum_unused += current->unused_numbers[unused_iterator];

							printf("Sum of unused indexes: %d\n", sum_unused);
							printf("Winning number: %d\n", check_values[value_iterator]);
							final_score = sum_unused*check_values[value_iterator];
							printf("Huzzah, a board won! Final score: %d\n", final_score);
							return;
						}
					}
					col++;
				}
				col = 0;
				row++;
			}
			row = 0;
			col = 0;
			current = current->next;
		}
		value_iterator++;
	}

	current = first;
	while (current) {
		garbage_board = current;
		current = current->next;
		free(garbage_board);
	}
}

void execute_day4_puzzle2() {
	char *file_buffer = NULL,*value = NULL;
	register int i = 0;
	int check_values[100];
	int value_iterator = 0, sum_unused = 0, final_score = 0, buffer_length = 0;

	ADVENT_BINGO_BOARD *first = NULL, *current = NULL, *garbage_board = NULL;

	value = malloc(sizeof(char)*3);
	if (!value)
		return;

	value[0] = '\0';

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day4\0");
	buffer_length = strlen(file_buffer);
	first = load_bingo_boards(file_buffer, buffer_length);
	while (i <= 290) {
		if (i == 0) {
			value[0] = file_buffer[i];
			value[1] = file_buffer[i+1];
			value[2] = '\0';
			check_values[value_iterator] = strtol(value, NULL, 10);
			value_iterator++;
			i = i + 3;
			continue;
		}
		if (file_buffer[i-1] == ',' || file_buffer[i+1] == ',') {
			if (file_buffer[i-1] == ',') 
				value[0] = file_buffer[i];	

			if (file_buffer[i+1] != ',') {
				value[1] = file_buffer[i+1];
				value[2] = '\0';
				i = i + 3;
			}
			else {
				value[1] = '\0';
				i = i + 2;
			}

			check_values[value_iterator] = strtol(value, NULL, 10);
			value_iterator++;
			continue;
		}
		i++;
	}

	if (!first) {
		printf("Failed to load bingo boards!\n");
		return;
	}	

	register int row = 0, col = 0;
	int unused_iterator = 0;
	value_iterator = 0;
	while (value_iterator < 101) {
		current = first;
		while (current) {
			if (current->winner == 0) {
				while (row < 5) {
					while (col < 5) {
						if (current->board[row][col] == check_values[value_iterator]) {
							current->rows[row]++;
							current->cols[col]++;

							for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) {
								if (current->unused_numbers[unused_iterator] == check_values[value_iterator]) {
									current->unused_numbers[unused_iterator] = 0;
								}
							}

							if (current->rows[row] == 5) {
								// process winner
								sum_unused = 0;
								final_score = 0;
								for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) 
									sum_unused += current->unused_numbers[unused_iterator];

								final_score = sum_unused*check_values[value_iterator];
								col = 6;
								row = 6;
								current->winner = 1;
								continue;
							}

							if (current->cols[col] == 5) {
								// process winner
								sum_unused = 0;
								final_score = 0;
								for (unused_iterator = 0; unused_iterator < 25; unused_iterator++) 
									sum_unused += current->unused_numbers[unused_iterator];

								final_score = sum_unused*check_values[value_iterator];
								col = 6;
								row = 6;
								current->winner = 1;
								continue;
							}
						}
						col++;
					}
					col = 0;
					row++;
				}

				if (final_score > 0)
					printf("Huzzah, a board won! Final score: %d\n", final_score);
			}
			row = 0;
			col = 0;
			current = current->next;
		}
		value_iterator++;
	}

	current = first;
	while (current) {
		garbage_board = current;
		current = current->next;
		free(garbage_board);
	}
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

ADVENT_COORDINATE_LINE* load_coordinate_lines(char* file_buffer, int skip_sloped_lines) {
	char *value = NULL, *sub_str = NULL;
	register int i = 0, y = 0;
	int reading_value = 0, buffer_length = 0, group_id = 0;

	ADVENT_COORDINATE_LINE *first = NULL, *current = NULL;

	value = malloc(sizeof(char)*4);
	if (!value)
		return NULL;

	first = malloc(sizeof(ADVENT_COORDINATE_LINE));
	if (!first)
		return NULL;


	first->x1 = 0;
	first->x2 = 0;
	first->y1 = 0;
	first->y2 = 0;
	first->next = NULL;
	first->last = NULL;
	first->hits = 0;
	first->id = group_id;
	current = first;
	current->first = first;
	group_id++;

	buffer_length = strlen(file_buffer);
	while (i < buffer_length) {
		if (file_buffer[i] == '>') {
			i++;
			continue;
		}

		if (file_buffer[i] == ' ') {
			i++;
			continue;
		}

		if (file_buffer[i] == '-') {
			i++;
			continue;
		}

		if (file_buffer[i] == '\n') {
			i++;
			continue;
		}

		if (file_buffer[i] == ',') {
			i++;
			continue;
		}

		if (reading_value == 0) {
			y = i;
			while (y < i+4) {
				if (file_buffer[y] == ',')
					break;
				else
					y++;
			}

			sub_str = substring(file_buffer, i, y-1);
			current->x1 = strtol(sub_str, NULL, 10);
			//printf("Got first substring: %d\n", current->x1);
			i = y;
			reading_value++;
		}
		else if (reading_value == 1) {
			y = i;
			while (y < i+4) {
				if (file_buffer[y] == ' ')
					break;
				else
					y++;
			}

			sub_str = substring(file_buffer, i, y-1);
			current->y1 = strtol(sub_str, NULL, 10);
			//printf("Got first substring: %d\n", current->y1);
			i = y;
			reading_value++;
		}
		else if (reading_value == 2) {
			y = i;
			while (y < i+4) {
				if (file_buffer[y] == ',')
					break;
				else
					y++;
			}

			sub_str = substring(file_buffer, i, y-1);
			current->x2 = strtol(sub_str, NULL, 10);
			//printf("Got first substring: %d\n", current->x2);
			i = y;
			reading_value++;
		}
		else if (reading_value == 3) {
			y = i;
			while (y < i+4) {
				if (file_buffer[y] == '\n')
					break;
				else
					y++;
			}

			sub_str = substring(file_buffer, i, y-1);
			current->y2 = strtol(sub_str, NULL, 10);

			if (current->y1 == current->y2 || current->x1 == current->x2) {
				//printf("Got first substring: %d\n", current->y2);
				i = y;
				reading_value++;

				current->next = malloc(sizeof(ADVENT_COORDINATE_LINE));
				if (!current->next)
					return NULL;

				current->points = get_my_line(current);
				current->next->last = current;
				current->next->first = current->first;
				current = current->next;
				current->x1 = 0;
				current->x2 = 0;
				current->y1 = 0;
				current->y2 = 0;
				current->next = NULL;
				current->hits = 0;
				current->id = group_id;
				group_id++;
			}
			else if (skip_sloped_lines == 1) {
				i = y;
				reading_value++;
				printf("Skipping sloped line (%d,%d) -> (%d, %d)\n", current->x1, current->y1, current->x2, current->y2);
				group_id++;
			}
			else {
				i = y;
				reading_value++;

				current->next = malloc(sizeof(ADVENT_COORDINATE_LINE));
				if (!current->next)
					return NULL;

				current->points = get_my_line(current);
				current->next->last = current;
				current->next->first = current->first;
				current = current->next;
				current->x1 = 0;
				current->x2 = 0;
				current->y1 = 0;
				current->y2 = 0;
				current->next = NULL;
				current->hits = 0;
				current->id = group_id;
				group_id++;

			}
		}
		if (reading_value == 4)
			reading_value = 0;
	}

	return first;
};

ADVENT_COORDINATE_POINT* get_my_line(ADVENT_COORDINATE_LINE *starting_points) {
	int change_in_x = 0, change_in_y = 0, has_next_point = 1, i = 0;
	//int slope = 0;

	if (starting_points->x1 > starting_points->x2)
		//change_in_x = starting_points->x1 - starting_points->x2;
		change_in_x = -1;
	else if (starting_points->x1 < starting_points->x2)
		change_in_x = 1;
	else
		change_in_x = 0;

	if (starting_points->y1 > starting_points->y2)
		//change_in_y = starting_points->y1 - starting_points->y2;
		change_in_y = -1;
	else if (starting_points->y1 < starting_points->y2)
		change_in_y = 1;
	else
		change_in_y = 0;

	ADVENT_COORDINATE_POINT *line = NULL, *first = NULL;
	first = malloc(sizeof(ADVENT_COORDINATE_POINT));
	if (!first)
		return NULL;

	first->next = NULL;	
	first->first = NULL;
	line = first;
	line->first = first;

	while (has_next_point == 1) {
		line->x = (i*change_in_x) + starting_points->x1; 
		line->y = (i*change_in_y) + starting_points->y1; 
		line->overlaps = 1;
		i++;

		printf("Plotting point for line %d: (%d,%d)\n", starting_points->id, line->x, line->y);
		if (line->x == starting_points->x2 && line->y == starting_points->y2) {
			has_next_point = 0;
			line->next = NULL;
		}
		else {
			line->next = malloc(sizeof(ADVENT_COORDINATE_POINT));
			if (!line->next)
				return NULL;

			line = line->next;
			line->first = first;
		}
	}

	return first;
};

int loop_and_count_hits(ADVENT_COORDINATE_LINE* starter, ADVENT_COORDINATE_POINT* all_points) {
	if (!starter)
		return 0;

	int hits = 0;
	ADVENT_COORDINATE_POINT *starting_line = NULL, *loop_line = NULL, *nested_looper = NULL;
	ADVENT_COORDINATE_LINE *current = NULL;

	current = starter->first;
	starting_line = starter->points;
	if (!starting_line)
		return 0;

	// iterate all lines
	while (current) {
		// skip current line, do not compare to self

		printf("Starting line %d\n", current->id);
		loop_line = current->points;
		if (!loop_line)
			break;

		// loop_line is line from CURRENT iteration
		while (loop_line) {
			nested_looper = all_points->first;
			while (nested_looper) {
				if (loop_line->x == nested_looper->x && loop_line->y == nested_looper->y) {
					nested_looper->overlaps++;
				}

				//printf("Point (%d, %d) now has %d overlaps, bisected from line %d\n", loop_line->x, loop_line->y, nested_looper->overlaps, current->id);
				nested_looper = nested_looper->next;
			}

			loop_line = loop_line->next;

		}
		loop_line = NULL;
		current = current->next;
	}

	return hits;
}

ADVENT_COORDINATE_POINT* load_all_points() {
	ADVENT_COORDINATE_POINT *first_point = NULL, *current_point = NULL;
	register int i = 0, y = 0;

	first_point = malloc(sizeof(ADVENT_COORDINATE_POINT));
	if (!first_point)
		return NULL;

	first_point->x = 0;
	first_point->y = 0;
	first_point->overlaps = 0;
	first_point->next = NULL;
	current_point = first_point;
	current_point->first = first_point;

	for (i = 0; i < 1000; i++) {
		for (y = 0; y < 1000; y++) {
			current_point->x = i;
			current_point->y = y;
			current_point->overlaps = 0;
			current_point->next = malloc(sizeof(ADVENT_COORDINATE_POINT));
			if (!current_point->next)
				return NULL;

			current_point = current_point->next;
			current_point->first = first_point;
		}
	}

	return first_point;
}

void execute_day5_puzzle1() {
	char *file_buffer = NULL;
	ADVENT_COORDINATE_LINE *first = NULL, *current = NULL, *garbage_line = NULL;
	ADVENT_COORDINATE_POINT *all_points = NULL, *looper = NULL, *garbage_loop = NULL;
	int greater_than_2 = 0;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day5\0");
	first =	load_coordinate_lines(file_buffer, 1);
	current = first;
	all_points = load_all_points();
	if (!all_points) {
		printf("Got no points for comparison!\n");
		return;
	}

	loop_and_count_hits(current, all_points);

	looper = all_points->first;
	while (looper) {
		garbage_loop = looper;
		if (looper->overlaps >= 2)
			greater_than_2++;

		looper = looper->next;
		free(garbage_loop);
	}

	while (current) {
		garbage_line = current;
		current = current->next;
		free(garbage_line);
	}

	printf("Lines with at least two hits: %d\n", greater_than_2);
};

void execute_day5_puzzle2() {
	char *file_buffer = NULL;
	ADVENT_COORDINATE_LINE *first = NULL, *current = NULL, *garbage_line = NULL;
	ADVENT_COORDINATE_POINT *all_points = NULL, *looper = NULL, *garbage_point = NULL;
	int greater_than_2 = 0;

	file_buffer = read_file_to_buffer("/home/arch/code/c/Advent/input/day5\0");
	first =	load_coordinate_lines(file_buffer, 0);
	current = first;
	all_points = load_all_points();
	if (!all_points) {
		printf("Got no points for comparison!\n");
		return;
	}

	loop_and_count_hits(current, all_points);

	looper = all_points->first;
	while (looper) {
		garbage_point = looper;
		if (looper->overlaps >= 2)
			greater_than_2++;

		looper = looper->next;
		free(garbage_point);
	}

	while (current) {
		garbage_line = current;
		current = current->next;
		free(garbage_line);
	}

	printf("Lines with at least two hits: %d\n", greater_than_2);

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
