#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>

#define FILENAME "lermontov.txt"

// Signal handler for SIGINT (Ctrl+C)
void handle_signal(int sig) {
	printf("\nReceived signal %d. Ignoring...\n", sig);
}

void create_and_write_file(const char *filename) {
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("Error creating file");
		exit(EXIT_FAILURE);
	}

	const char *text =
		"Выхожу один я на дорогу;\n"
		"Сквозь туман кремнистый путь блестит;\n"
		"Ночь тиха. Пустыня внемлет богу,\n"
		"И звезда с звездою говорит.\n";
	write(fd, text, strlen(text));
	close(fd);
}

void read_and_print(const char *fliname) {
	int fd = open(fliname, O_RDONLY);
	if (fd == -1) {
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}

	char buffer[256];
	ssize_t bytes;
	printf("\nFile content:\n");
	while ((bytes = read(fd, buffer, sizeof(buffer)-1)) > 0) {
		buffer[bytes] = '\0';
		printf("%s", buffer);
	}
	close(fd);
}

// cc -Wall -Wextra -Werror read.c && ./a.out
int main() {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));  // Zero out the struct
	sa.sa_handler = handle_signal;  // Set the handler function
	sigemptyset(&sa.sa_mask);	   // No signals blocked during execution
	sa.sa_flags = 0;				// No special flags

	// SIGINT (Ctrl + C)
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}
	create_and_write_file(FILENAME);
	if (access(FILENAME, F_OK) == 0)
		printf("Fiel '%s' exists.\n", FILENAME);
	else {
		perror("File access error");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		printf("Child process (PID %d) reading file...\n", getpid());
		read_and_print(FILENAME);
		exit(0);

	} else {
		int status;
		struct  rusage usage;
		printf("Parent process (PID %d) waiting for child (PID %d)...\n", getpid(), pid);
		
		wait(&status);
		waitpid(pid, &status, 0);
		wait3(&status, 0, &usage);
		wait4(pid, &status, 0, &usage);
		printf("Child process finished.\n");
	}
	return (0);
}

/*
A signal is an asynchronous notification sent to a process by:

The kernel (e.g., when a process divides by zero).
Another process (using kill() or raise()).
The user (pressing Ctrl+C sends SIGINT).
Signals can:  Terminate a process (SIGKILL, SIGTERM).
 Pause a process (SIGSTOP, SIGTSTP).
 Continue a paused process (SIGCONT).
 Trigger a custom handler (SIGINT, SIGHUP)
 SIGINT	2	Terminate	Interrupt from keyboard (Ctrl+C)
SIGTERM	15	Terminate	Request to terminate (kill <pid>)
SIGKILL	9	Terminate	Forcefully kill a process (cannot be caught)
SIGSTOP	19	Stop	Pause process (Ctrl+Z)
SIGCONT	18	Continue	Resume a paused process
SIGSEGV	11	Terminate	Segmentation fault (invalid memory access)
SIGALRM	14	Terminate	Alarm signal (alarm())

struct sigaction is a structure used in the sigaction() system call to define how a program handles signals in C.
It allows us to: Set a custom signal handler function
Block specific signals while handling another
Control how signals behave (e.g., restart system calls)
struct sigaction {
	void (*sa_handler)(int);  // Pointer to the signal handler function
	sigset_t sa_mask;		 // Signals to block while handling current signal
	int sa_flags;			 // Special options for handling signals
};

sigaction() vs. signal()
Feature					signal()	sigaction()
Basic usage				✅ Yes		❌ No (More complex)
Portability				❌ No		✅ Yes
Can block signals		❌ No		✅ Yes (sa_mask)
Controls behavior		❌ No		✅ Yes (sa_flags)
Works reliably			❌ No		✅ Yes
struct sigaction controls how a signal is handled.
Use sigaction() instead of signal() for better control.
sa_handler defines the handler function.
sa_mask blocks other signals while handling.
sa_flags changes behavior (e.g., SA_RESTART)


#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
Parameter	Description
signum		The signal to catch (e.g., SIGINT).
act			The new signal action (handler and options).
oldact		Stores the previous action (can be NULL if not needed).
memset(&sa, 0, sizeof(sa)); // Ensures all fields are zeroed
sa.sa_handler = handle_signal; // Assign signal handler
sigemptyset(&sa.sa_mask); // Clears the signal mask
sa.sa_flags = 0; // No special flags
sa.sa_handler → Assigns the signal handler function.
sigemptyset(&sa.sa_mask) → Clears the mask set (which signals should be blocked while handling this one).
sa.sa_flags = 0 → Uses default behavior.

perror()
When a system call fails, it sets the global variable errno.
perror() reads errno and prints an error message.
The message comes from strerror(errno), which maps error numbers to messages

#include <unistd.h>
int access(const char *pathname, int mode);
Checks if a file exists and if the calling process has certain permissions (R_OK, W_OK, X_OK, F_OK).

#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
Theory:
Writes count bytes from buf to the file descriptor fd.
Returns the number of bytes written.

#include <unistd.h>
int close(int fd);
Releases the file descriptor fd after reading/writing.

. wait() - Wait for a Child Process to Terminate
Synopsis:
c
Copy
Edit
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
Theory:
Blocks the parent process until any child process terminates.
status stores the child’s termination status.

#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
Theory:
Blocks the parent process until any child process terminates.
status stores the child’s termination status.

pid_t waitpid(pid_t pid, int *status, int options);
Theory:
Similar to wait() but allows waiting for a specific child process

pid_t wait3(int *status, int options, struct rusage *rusage);
Theory:
Like wait(), but provides resource usage (CPU time, memory usage).
rusage contains detailed statistics.

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
Theory:
Similar to wait3(), but waits for a specific child process.
#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
Theory:
More powerful than signal(), allowing control over signal handling.
Example:
c
Copy
Edit
struct sigaction sa;
sa.sa_handler = handle_signal;
sigaction(SIGINT, &sa, NULL);
*/