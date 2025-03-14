#include <unistd.h>
#include <stdio.h>

// cc -Wall -Wextra -Werror terminal_handle.c && ./a.out
int main()
{
    if (isatty(STDIN_FILENO)) {
        printf("Std input is a terminal.\n");
    } else {
        printf("Std input is not a terminal.\n");
    }

    char *terminal_name = ttyname(STDIN_FILENO);
    if (terminal_name)
        printf("Term devise: %s\n", terminal_name);
    else
        printf("No term. associated with this fd.\n");
    return (0);
}

/*
The isatty function checks whether a file descriptor refers to a terminal device. This is useful in determining whether input/output is being redirected.

The ttyname function returns the name of the terminal associated with a given file descriptor. If the file descriptor is not connected to a terminal, ttyname returns NULL.

/dev/pts/7 is a pseudo-terminal device.
pts stands for pseudoterminal slave.
The 7 represents the specific pseudoterminal number assigned by the system.
What is a Pseudoterminal (PTY)?
A pseudoterminal (PTY) is a pair of virtual devices that emulate a terminal. It is used by programs like ssh, screen, tmux, and terminal emulators (such as xterm, gnome-terminal, konsole, etc.).

In a PTY system, there are two sides:

Master side (/dev/ptmx) – Handled by the terminal emulator.
Slave side (/dev/pts/X) – Acts like a real terminal, allowing interaction with shell processes.
Your /dev/pts/7 is the slave side of the terminal session running your program.

You ran the program inside a terminal emulator.
The terminal emulator assigns a pseudoterminal (PTY) to handle input and output.
Your standard input (STDIN_FILENO) is linked to a PTY.
ttyname(STDIN_FILENO) retrieved the name /dev/pts/7, indicating that your session's terminal input is managed by the 7th PTY.

Why Are Pseudoterminals Used?
Allows remote sessions (ssh uses /dev/pts/* for managing terminal sessions).
Enables multiple terminal windows (tmux, screen).
Supports GUI terminal emulators (gnome-terminal, xterm, etc.).
Provides isolation so each session can run independently.

To see all currently active pseudoterminals:
ls -l /dev/pts/
You can check your current terminal using:
tty
This should output:
/dev/pts/7

/dev/pts/7 is a pseudoterminal that represents your terminal session.
It exists because you're using a terminal emulator.
TTY programs use it to manage user input/output.
You can list active PTYs using ls /dev/pts/.
To verify your terminal, run tty in the shell.
This system allows flexible session management, supporting remote logins, multiple shells, and terminal multiplexing.
*/