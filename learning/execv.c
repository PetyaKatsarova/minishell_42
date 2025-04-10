#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// cc -Wall -Wextra -Werror execv.c && ./a.out
int main() {
	pid_t pid = fork();
	if (pid == 0) {
		char *args[] = {"/bin/ls", "-l", NULL};
		execve("/bin/ls", args, NULL);
	} else {
		printf("Parent process waiting...\n");
		wait(NULL);
		printf("Child process finished.\n");
	}
	return (0);
}