#ifndef FILE_H
#define FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WINDOWS
	#include <windows.h>
#endif
#ifndef WINDOWS
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <errno.h>
	#include <fcntl.h>
#endif

#include <stdio.h>
#include "core.h"
#include "config.h"

int ensure_dir_exists(char *buffer, char* l1, char* l2);
int ensure_file_exists(char *buffer, char* l1, char* l2);
char* get_current_directory(char *buffer);
char* read_file_to_buffer(char* fileName);
int validate_directory(char *directory);
int read_files_in_landing_directory(char **files);
char** read_files_in_directory(char *directory);
int copy_file(const char *to, const char *from);

#ifdef __cplusplus
}
#endif

#endif
