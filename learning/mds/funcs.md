# C Functions Tutorial

## 1. Readline Functions

### `readline`

The `readline` function reads a line from standard input with editing capabilities, allowing users to navigate and modify the input before submitting it. This function is useful for interactive applications like command-line shells, as it provides built-in line editing, history management, and command completion.

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input = readline("Enter command: ");
    if (input && *input) { // Ensure input is not NULL or empty
        add_history(input); // Store input in history
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}
```

### `rl_clear_history`

Clears the readline history, which is useful for freeing memory or resetting a session. This function is often used in command-line interfaces that store previous user inputs for quick access.

```c
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    add_history("test");
    rl_clear_history();
    return 0;
}
```

### `rl_replace_line`

Replaces the current input line with a specified string. This is useful for dynamically modifying user input before execution, such as in interactive debugging or command-line editing.

```c
#include <readline/readline.h>

int main() {
    rl_replace_line("Modified input", 0);
    rl_redisplay();
    return 0;
}
```

---

## 2. File Handling

### `open` and `write`

The `open` function is used to open a file, returning a file descriptor, while `write` writes data to the file. The file descriptor is a low-level handle used by the operating system to track open files.

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    char *text = "Hello, file!";
    write(fd, text, 12);
    close(fd);
    return 0;
}
```

### `read`

The `read` function reads data from a file descriptor into a buffer. It returns the number of bytes read, which may be less than the requested amount.

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[100];
    int fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Read: %s\n", buffer);
    }
    close(fd);
    return 0;
}
```

---

## 3. Process Management

### `fork` and `execve`

The `fork` function creates a child process, and `execve` replaces the current process image with a new program. The parent process waits for the child to complete execution.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
    return 0;
}
```

---

## 4. Directory Handling

### `opendir` and `readdir`

The `opendir` function opens a directory stream, while `readdir` iterates over directory entries. These functions are useful for listing files in a directory.

```c
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
```

---

## 5. Terminal Handling

### `isatty` and `ttyname`

The `isatty` function checks whether a file descriptor refers to a terminal device. This is useful in determining whether input/output is being redirected.

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (isatty(STDIN_FILENO)) {
        printf("Standard input is a terminal.\n");
    } else {
        printf("Standard input is not a terminal.\n");
    }
    return 0;
}
```

The `ttyname` function returns the name of the terminal associated with a given file descriptor. If the file descriptor is not connected to a terminal, `ttyname` returns `NULL`.

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *terminal_name = ttyname(STDIN_FILENO);
    if (terminal_name) {
        printf("Terminal device: %s\n", terminal_name);
    } else {
        printf("No terminal associated with this file descriptor.\n");
    }
    return 0;
}
```

---

This tutorial provides a structured guide to key C functions used for file handling, process management, directory handling, and terminal control. Each function includes theoretical explanations and example usage.

