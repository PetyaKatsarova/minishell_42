#include <stdio.h>	  // For printf()
#include <unistd.h>	 // For getcwd(), chdir()
#include <limits.h>	 // For PATH_MAX
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void print_file_info(const char *filename) {
	struct stat file_stat;

	if (stat(filename, &file_stat) == -1) {
		perror("stat failed");
		return;
	}

	printf("File: %s\n", filename);
	printf("Size: %ld bytes\n", file_stat.st_size);
	printf("Permissions: %o\n", file_stat.st_mode & 0777);
	printf("Owner UID: %d\n", file_stat.st_uid);
	printf("Last modified: %ld\n\n", file_stat.st_mtime);	
}

void demo_lstat(const char *filename) {
	struct stat file_stat;

	if (lstat(filename, &file_stat) == -1) {
		perror("lstat failed");
		return;
	}

	printf("[lstat] File: %s\n", filename);
	if (S_ISLNK(file_stat.st_mode)) {
		printf("This is a symbolic link.\n");
	} else {
		printf("This is NOT a symbolic link.\n");
	}
	printf("\n");
}

void demo_fstat(int fd) {
	struct stat file_stat;

	if (fstat(fd, &file_stat) == -1) {
		perror("fstat failed");
		return;
	}

	printf("[fstat] File descriptor info:\n");
	printf("Size: %ld bytes\n", file_stat.st_size);
	printf("Owner UID: %d\n", file_stat.st_uid);
	printf("\n");
}


// cc -Wall -Wextra -Werror working_dir.c && ./a.out
int main() {
	char cwd[PATH_MAX]; // curr working dir
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current directory: %s\n", cwd);
	} else {
		perror("getcwd failed");
		return 1;
	}
		// Change directory to the parent directory
	if (chdir("..") == 0) {
		getcwd(cwd, sizeof(cwd));
		printf("Changed directory: %s\n\n", cwd);
	} else {
		perror("chdir failed");
		return 1;
	}
	// create test file
	printf("Creating file in directory: %s\n", cwd);
	const char *filename = "blabla.txt";
	int fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1) {
		perror("open failed");
		return 1;
	}
	write(fd, "Hello, world!\n", 14);
	close(fd);
	// Use stat() to get file metadata
	print_file_info(filename);
	
	// check if it's a symbolic link
	demo_lstat(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open failed");
		return 1;
	}
	demo_fstat(fd);
	close(fd);
		// 7. Delete the file using unlink()
	if (unlink(filename) == 0) {
		printf("File '%s' deleted successfully.\n", filename);
	} else {
		perror("unlink failed");
	}
	return (0);
}

/*
Getting the current working directory (getcwd()).
Changing the working directory (chdir()).
Retrieving file metadata using stat(), lstat(), and fstat().
Deleting a file (unlink()).

cwd (Current Working Directory): This stores the absolute path of the directory where the program is currently running.
PATH_MAX: This is the maximum length for a valid path in the operating system.
getcwd(): Retrieves the current working directory.
chdir(): Changes the working directory.

PATH_MAX
On Linux, it's typically 4096.
On Windows, it can be 260 (but configurable).
If the path exceeds PATH_MAX, some functions may fail.

getcwd(cwd, sizeof(cwd))
Fetches the current directory path and stores it in cwd.
sizeof(cwd) ensures we don’t exceed the buffer limit.
Returns NULL on failure (e.g., if cwd is too small).
Possible failures:
Insufficient buffer size.
Permission issues.

chdir("..")
Moves one level up in the directory hierarchy.
".." is the parent directory.
Returns 0 on success, -1 on failure.
Second getcwd()
Retrieves the new current directory after chdir().

struct dirent is a structure defined in <dirent.h> that represents a directory entry (file or subdirectory) when reading a directory in C. It is used with the readdir() function to iterate over files and directories.

 The  functions  snprintf() and vsnprintf() write at most size bytes (including the terminating null byte ('\0')) to str.
*/