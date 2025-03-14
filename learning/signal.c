#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    printf("Caught signal %d\n", signo);
}

// cc -Wall -Wextra -Werror signal.c && ./a.out
int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    printf("Printf Ctrl+C to trigger SIGINT\n");
    while (1) {
        sleep(1);
    }
    return (0);
}

/*
sigaction(SIGINT, &sa, NULL): Registers signal_handler for SIGINT (Ctrl+C).

sigemptyset(&sa.sa_mask): Ensures the signal mask is empty.

kill(getpid(), SIGINT): Sends SIGINT to itself.

exit(1): Terminates the process safely.
*/