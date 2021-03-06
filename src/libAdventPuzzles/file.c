#include "file.h"

char* get_current_directory(char *buffer) {
#ifdef WINDOWS
	int toTrim = 0;
	GetModuleFileName( NULL, buffer, MAX_PATH );
	toTrim = backwards_find_index(buffer, '\\'); 
	if (toTrim != -1) {
		buffer = (char*)substring(tmp, 0, toTrim);
	}
	return tmp;
#else
	if (getcwd(buffer, MAX_PATH) != NULL) {
		return buffer;
	} else {
		perror("getcwd() error");
		return NULL;
	}
	return NULL;
#endif
}

int ensure_dir_exists(char *buffer1, char* l1, char* l2) {
	char buffer[MAX_PATH];
	get_current_directory(buffer);

#ifdef WINDOWS
	strcat(buffer, l1);
	if (l2 != NULL) {
		strcat(buffer, "\\");
		strcat(buffer, l2);
	}
	printf("Current directory: %s\n", buffer);
	if (CreateDirectory(buffer, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}
	else {
		return -1;
	}

	return 0;
#else
	strcat(buffer, "/");
	strcat(buffer, l1);
	if (l2 != NULL) {
		strcat(buffer, "/");
		strcat(buffer, l2);
	}
	printf("Current directory: %s\n", buffer);
	// Failed to create directory.
	DIR* directory = opendir(buffer);
	if (directory) {
		closedir(directory);
		return 1;
	}
	else if (ENOENT == errno) {
		if (mkdir(buffer, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
			return 1;
		}
	}
	else {
		/* opendir() failed for some other reason. */
		return -1;
	}

	return 0;
#endif
}

int ensure_file_exists(char *buffer1, char* l1, char* l2) {
	char buffer[MAX_PATH];
	get_current_directory(buffer);
	if (buffer1) {
		strcpy(buffer, buffer1);
	}

#ifdef WINDOWS
	if (l1 != NULL) {
		strcat(buffer, "\\");
		strcat(buffer, l1);
		if (l2 != NULL) {
			strcat(buffer, "\\");
			strcat(buffer, l2);
		}
	}

	printf("Checking for file: %s\n", buffer);
#else
	if (l1 != NULL) {
		strcat(buffer, "/");
		strcat(buffer, l1);
		if (l2 != NULL) {
			strcat(buffer, "/");
			strcat(buffer, l2);
		}
	}

	printf("Checking for file: %s\n", buffer);
#endif

	FILE *fp = fopen(buffer, "ab+");
	if (fp) {
		fclose(fp);
		return 1;
	}
	else {
		return -1;
	}

	return 0;
}

char* read_file_to_buffer(char* fileName) {
	char *buffer = 0;
	long length;

	//TODO: Add Error checking
	FILE *f = fopen (fileName, "rb");
	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length + 1);
		if (buffer) {
			fread (buffer, 1, length, f);
		}
		fclose (f);
		buffer[length] = '\0';
	}

	return buffer;
}

int validate_directory(char *directory) {

	return 0;
}

char** read_files_in_directory(char *directory) {
	DIR *d;
	struct dirent *dir;
	char **file_names = NULL;
	int i = 0, loop_end = 9;

	// Let's start with room for 10 files, can realloc if needed
	file_names = malloc(10 * sizeof(char*));
	if (!file_names) {
		//implement error library
		return NULL;
	}

	d = opendir(directory);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (i > loop_end) {
				file_names = realloc(file_names, (i*2) * sizeof(char*));
				if (!file_names) {
					//implement error library
					return NULL;
				}
				loop_end += 10;
			}
			file_names[i] = malloc(strlen(dir->d_name)*sizeof(char)+4);
			strcpy(file_names[i], dir->d_name);
			i++;
		}
		closedir(d);
		return file_names;
	}
	else 
		return NULL;

}

int read_files_in_landing_directory(char **file_names) {
	DIR *d;
	struct dirent *dir;
	int i = 0;
	char landing_directory[MAX_PATH];

	get_current_directory(landing_directory);
	strcat(landing_directory, "/");
	strcat(landing_directory, "landing");

	d = opendir(landing_directory);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_name) {
				if (strncmp(dir->d_name, ".", 1) == 0 || strncmp(dir->d_name, "..", 2) == 0) {
					continue;
				}

				file_names[i] = malloc(strlen(dir->d_name)*sizeof(char)+4);
				strcpy(file_names[i], dir->d_name);
			}
			i++;
		}
		closedir(d);
		return i;
	}
	else 
		return -1;
}

int copy_file(const char *to, const char *from)
{
	int fd_to, fd_from;
	char buf[4096];
	ssize_t nread;
	int saved_errno;

	fd_from = open(from, O_RDONLY);
	if (fd_from < 0)
		return -1;

	fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd_to < 0)
		goto out_error;

	while (nread = read(fd_from, buf, sizeof buf), nread > 0)
	{
		char *out_ptr = buf;
		ssize_t nwritten;

		do {
			nwritten = write(fd_to, out_ptr, nread);

			if (nwritten >= 0)
			{
				nread -= nwritten;
				out_ptr += nwritten;
			}
			else if (errno != EINTR)
			{
				goto out_error;
			}
		} while (nread > 0);
	}

	if (nread == 0)
	{
		if (close(fd_to) < 0)
		{
			fd_to = -1;
			goto out_error;
		}
		close(fd_from);

		/* Success! */
		return 0;
	}

out_error:
	saved_errno = errno;

	close(fd_from);
	if (fd_to >= 0)
		close(fd_to);

	errno = saved_errno;
	return -1;
}
