#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

/**
 * Reads a line from standard input with editing capabilities.
 */

// cc -Wall -Wextra -Werror readline.c -lreadline && ./a.out

 int main() {
	char *input;

	while (1)
	{
		// input = readline("Enter command: "); gives automatically the prompt 
		printf("Enter command: "); // manual prompt instead readl
		fflush(stdout);			// Ensure it appears before readline()
		input = readline(""); // reads input without the auto prompt
		// !!NB!! Ctrl+D signals EOF (End of File) when reading from standard input.
		if (!input) { // Exit on Ctrl+D
			printf("\nExiting...\n");
			break;
		}
		if (*input)
			add_history(input); // arrow key navigation: past inputs
		printf("Original input: %s", rl_line_buffer);
		rl_on_new_line(); // signals a new line
		rl_replace_line("tra la la", 0); // replaces curr input line 
		// rl_redisplay(); // refreshes the command prompt display and immediately display on the shell
		printf("\nModified buffer: %s\n", rl_line_buffer);
		free(input);
	}
	rl_clear_history(); // clears memory from history
	return (0);
 }
 /*
 readline
 Supports arrow keys, history navigation, and auto-completion. char *readline(const char *prompt);
		 
 rl_clear_history
rl stands for readline
The rl_clear_history function clears the Readline history, freeing the memory used to store previous inputs. This is useful when you want to reset or prevent memory leaks in long-running applications. Calling this function ensures that past commands stored in memory are removed, but it does not affect saved history files.
the memory allocation for input and the history entry for that input are separate.
The prefix rl_ in Readline functions stands for "Readline Library". It is used as a namespace to group related functions together, preventing naming conflicts with other libraries. Functions like rl_clear_history, rl_replace_line, and rl_redisplay are all part of the GNU Readline library and provide powerful command-line input handling features.
You won't find rl_on_new_line() in the standard shell man pages. It is part of the GNU Readline Library, and its documentation is typically found in:

1. Readline Info Manual (if installed)
info readline

GNU stands for "GNU's Not Unix".

It is a recursive acronym, meaning the first letter stands for the acronym itself. The GNU Project was started in 1983 by Richard Stallman to create a free, Unix-like operating system.
It is free software, meaning users can run, modify, and distribute it.
The GNU system includes essential tools like GNU Compiler Collection (GCC), GNU Readline, Bash, and GNU Core Utilities (coreutils).
It forms the foundation of Linux-based operating systems, which are technically GNU/Linux (since Linux is just the kernel).

extern char *rl_line_buffer;
Since it is extern, it is available globally in any program that includes <readline/readline.h>.

fflush(stdout); forces the output buffer to be written immediately to the terminal.
Instead of printing immediately, printf() stores data in a buffer and prints it when the buffer is full or when a newline (\n) is encountered.

The issue is that rl_replace_line("tra la la", 0); updates the Readline buffer before the next prompt is displayed, and rl_redisplay(); forces it to be shown on the screen. That’s why "tra la la" appears unexpectedly.
 */