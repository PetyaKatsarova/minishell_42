Built-in commands (echo, cd, pwd, export, unset, env, exit) must not use execve because they don't spawn a new process. A built-in command is part of the shell itself (e.g., cd, echo, export). It runs without needing an external file.How to Check if a Command is Built-in or External?
type uname

User keyboard signals:
ctrl-c displays a new prompt line.
ctrl-d exits minishell
ctrl-\ does nothing
Minishell does not support \, ;, &&, ||, or wildcards.

ctr+\ is  (SIGQUIT) core dumped

A pipe is a sort of file, stored outside of the file system, that has no name or any other particular attribute.
On success, pipe returns 0. However, on failure, it returns -1 and describes the encountered error in errno, without filling the provided table.
But we can handle it like a file thanks to its two file descriptors.
In order to establish inter-process communication between a parent and child process, we will first have to create a pipe. Then, when we create the child,
 it will have a duplicate of the pipe’s descriptors, since a child process is a clone of its parent. This way, the child will be able to read from 
 pipefd[0] information written by the parent in pipefd[1] and vice versa. Of course, we could also allow two child processes to communicate with each 
 other in this way.
 If a process attempts to read from an empty pipe, read will remain blocked until data is written to it.
Inversely, if a process tries to write to a full pipe (one that has reached its size limit), write will remain blocked until enough data has been 
read to allow the write operation to complete.
To ensure that the processes correctly receive the termination indicators (EOF, SIGPIPE/EPIPE), it is essential to close all unused duplicate file 
descriptors. Otherwise, we risk processes getting stuck in a suspended state.

cat test.txt | wc -l, the contents of the file don’t appear at all. So what is this “|” operator doing here exactly?

## PIPE | cat text.txt | wc -l
The shell creates a pipe and two child processes, one for the cat command and one for wc. Then, it redirects cat‘s standard output towards wc‘s 
standard input. Therefore, the cat command does not write its output in the standard output (our terminal), but rather in the pipe. Then, the wc 
command will go looking for the data in that pipe rather than the standard input.
man bash | head -n 50 | grep shell | grep bash | wc -l. This is called a pipeline.

To build a pipeline, we need to create a pipe (a pair of file descriptors) for each child process, minus 1. That way, the first child can write on
its own pipe, the second can read from the first one’s and write to its own, and so on. And above all, we can’t forget to close all of the pipes’ 
unused file descriptors in each child process!

When we execute a program, whether it be with a shell command, by double-clicking an icon or automatically at startup, the system loads its
 instructions into RAM and executes them one after the other. A program in this state of execution is what we call a process.
A program exists on a hard drive; a process exists in RAM.

$ ps -eCode language: Shell Session (shell)
// above cmnd: to see all running processes
------------------------------------------
ps -e
ps → Process Status: Lists running processes.
-e → Show all processes (from all users, not just yours).
Columns:

PID → Process ID (unique number for each process).
TTY → Terminal where the process started (? means background process, meaning without a terminal).
TIME → CPU time used by the process.
CMD → Command that started the process.

ps -ef	Show all processes with full details.
ps aux	Show processes with more info, including memory usage.
ps -e --forest	Show processes in a tree view.

TTY	 Value				Meaning
pts/0	Pseudo-terminal	 (process running inside a terminal emulator like bash, ssh, tmux).
hvc0	Hypervisor Console  (used by WSL, virtual machines, or cloud instances).
?		No terminal		 (background system process, daemon, or service).

SessionLeader → Manages a login session.
Relay(607) → A relay process handling communication.

Git Bash is not real Bash, it’s MinGW (Minimalist GNU for Windows).
MinGW lacks Linux-style process management, so pidof doesn't exist.

echo "PID = $$; PPID = $PPID"
$$ → Current shell’s Process ID (PID).
$PPID → Parent Process ID (PPID).
-----------------------------------------

int fork();
The fork system call will allow our process to create a new process, which will be its exact clone and executed simultaneously.
As we’ve seen, a child process is an exact copy of its parent process. When a child is created, it is identical to its parent in every way. 
It has the same code, the same open file descriptors, the same data stored in memory, etc. But the fact that this memory is identical does not 
mean it is shared between the two processes. If the parent process changes the value of one of its variables after creating the child, the child 
process will not see any change when it reads the same variable.

Fundamentally, a zombie process isn’t a problem as long as the parent retrieves it. It consumes no energy and takes up no memory space.
Zombie processes are also automatically eliminated by their adoptive parent init if they become orphaned. However, if the parent is a process 
that is never intended to end (server, background process, etc.), that creates children regularly without ever waiting for them, the system’s
process table might very well get saturated. That would block the system, which would no longer be able to execute new processes.

options: waitpid offers several options. Among those, the sometimes very useful WNOHANG. With the WNOHANG option, waitpid returns immediately if the
child process has not ended yet. Without this option, the parent process will by default remain suspended as long as the child is still executing
its tasks.
If the system call succeeds, both wait and waitpid return the terminated child’s PID, otherwise, they return -1. The waitpid function can also
return 0 if the WNOHANG option was specified and if the child it is waiting for has not changed states yet.
The status is an integer that represents not only the exit code but also further details that explain why a child exited.

We can inspect the status thanks to several macros:

WIFEXITED(status): returns true if the child terminated normally, for example by calling exit or finishing through the main function of the program.
WEXITSTATUS(status): to be used only if WIFEXITED returned true. Returns the child’s exit code, meaning the number the child specified to the exit function or in the main function’s return.
WIFSIGNALED(status): returns true if the child was forcefully terminated by a signal.
WTERMSIG(status): to be used only if WIFSIGNALED returned true. Returns the signal number that provoked the child’s termination.
----------------------------------

#include <fcntl.h>  //File Control
Most used functions:
fcntl() – manipulate file descriptor
open() – open file
creat() – create file
close() – close file
read() – read from file
write() – write to file
lseek() – move file offset
dup()/dup2() – duplicate file descriptor
flock() – lock file
-----------------------------------------

int kill(pid_t pid, int sig);Code language: C++ (cpp)
pid: the PID of the process that we want to kill.
sig: the signal that we want to send to the process in order to kill it. There are many different possible signals for kill, each with its own nuances,
but the most frequently used are perhaps SIGTERM (soft termination signal) and SIGKILL (hard kill signal). functions returns 0 for success and -1 
for failure, with errno set to indicate error details. For further details.

A signal is a standardized notification message used in Unix and POSIX-compliant operating systems. It is asynchronously sent to a running 
program to notify it of some event. The system interrupts the process’ normal execution to trigger a specific reaction like, among other things, 
terminating it. So signals are a sort of inter-process communication.

The operating system’s kernel can send a signal for one of the two following reasons:
it has detected a system-wide event like a divide-by-zero error or the end of a child process,
a process requested a signal to be sent with the kill system call (a process can send itself a signal in this way).
In reality, “sending” a signal is more like delivering it: the system updates the destination process’ context. Indeed, for each process, 
the kernel maintains two bit vectors: pending, to monitor pending signals, and blocked, to keep track of the blocked signals. When it sends a 
signal, the kernel simply sets the appropriate bit to 1 in the destination process’ pending bit vector.

The operating system seems to be able to multitask, but this is only an illusion. In truth, it is constantly switching from one process to the next 
at lightning speed. This is called “context switching”.When the kernel resumes the execution of a process, for example after one of these context 
switches or after completing a system call, it checks the unblocked pending signal set. This is done with the 
bitwise operationpending & ~blocked. If that set is empty, as is usually the case, it moves on to the program’s next instruction. However, if the 
set is not empty, the kernel chooses a signal (typically the smallest) and forces the process to react to it with an action. This is the moment we call 
“receiving” the signal. Depending on is type, the process will either ignore the signal,terminate its own execution,
intercept the signal by executing its own handler in response.
Once the signal received and one of these actions performed, the kernel resets the corresponding bit in the pending bit vector and moves 
on to the following instruction if the program has not yet terminated.

1. What Does kill -l Do?
kill -l
Lists all available signal names that kill can send to a process.
Example output (on Linux):
1) SIGHUP   2) SIGINT   3) SIGQUIT   9) SIGKILL   15) SIGTERM
Each signal has a number and a name.
You can use either the number or the name.
2. How to Choose the Right Signal?
You need to replace [SIGNAL] with the right one:

Signal	Number	Effect		Usage			   Example
SIGTERM	15		Graceful	stop				kill -15 PID (default if no signal is given)
SIGKILL	9		   Force kill (cannot be blocked)	kill -9 PID
SIGHUP	1	Restart process (reload configs)	kill -1 PID
SIGINT	2	Interrupt (like Ctrl+C)				kill -2 PID
SIGSTOP	19	Pause process						kill -19 PID
SIGCONT	18	Resume paused process				kill -18 PID
3. Example: Kill a Process
kill -9 1234  # Force kill process with PID 1234
kill -15 5678 # Gracefully stop process 5678
kill -SIGSTOP 4321 # Pause process 4321
kill -SIGCONT 4321 # Resume process 4321
Use SIGTERM (kill PID) first.
Only use SIGKILL (kill -9 PID) if the process won't stop.
By default, a process receiving a signal will perform one of these four actions:

Terminate: the process immediately terminates,
Core: the process immediately terminates does a core dump (creates a file containing a copy of its memory and registers for future analysis),
Ignore: the signal is simply ignored and the program carries on with its regular execution,
Stop: suspends the process’ execution until it receives the SIGCONT signal.
n Unix-type systems, there are several mechanisms to send signals to processes. All of them use the concept of process groups.
Each process belongs to a group which is identified by a positive integer, the PGID (process group identifier). It’s an easy way to recognize related 
processes. By default, all child processes belong to their parent’s process group. This allows the system to send a single signal to all of the processes within a group at once.

However, a process can change its own group or the group of another process. This is what our shell does when it creates child processes to execute 
the user’s input. Let’s display the process identifier (PID), the parent process identifier (PPID) and the process group identifier (PGID) of all the 
processes associated with our shell with the ps command:

$ ps -eo "%c: [PID = %p] [PPID = %P] [PGID = %r]"  | grep $$

From the shell in our terminal, there are three keyboard shortcuts that allow us to interrupt all of the running foreground processes:

ctrl-c: sends SIGINT to interrupt them,
ctrl-\: sends SIGQUIT to kill them,
ctrl-z: sends SIGTSTP to suspend them.
Of course, these shortcuts do not affect background processes. But what if we want to send one of the 28 other signals instead?
$ /bin/kill -9 4242
$ /bin/kill -KILL 4242
$ /bin/kill -SIGKILL 4242Code language: Shell Session (shell)
Now, let’s say that the 4242 process has several children that belong to the 4242 group. How do we indicate that we mean the group 4242, not 
the process? For the kill command, a negative number means a PGID and not a PID. So in order to kill all of the processes in the 4242 group, we can:

$ /bin/kill -9 -4242
$ /bin/kill -KILL -4242
$ /bin/kill -SIGKILL -4242Code language: Shell Session (shell)

This system call works in much the same way as the /bin/kill command described above. Its parameters are:

pid: the identifier of the process or process group to send the signal to. Here, we can specify:
a positive integer: a process’ PID,
a negative integer: a process group’s PGID,
0: all of the processes in the calling process’ group,
-1: all of the processes in the system (except process 1, init!) for which the calling process has the permission to send signals to. See the manual 
page for kill (2) about permissions.
sig: the signal to send to the process.

Signals are asynchronous, which means that they can occur at any time during our program’s execution. When we intercept 
them with a handler, we never know where the program is in its execution. If the handler accesses a variable that the 
program is currently using, the results could be disastrous. And, we can’t forget that a handler can itself be 
interrupted by another handler (or itself!) if the process receives another signal in the meantime!
Signal handlers are a form of concurrent programming. Yet, as we’ve previously seen in the article about threads 
and mutexes, concurrent programming can cause unforeseeable and extremely difficult errors to debug. To avoid these 
kinds of errors, we should take a lot of care when formulating handlers, so that they are as safe as possible.
1. Keep signal handlers as simple and short as possible

Sometimes, all a handler has to do is set a flag and let the main program take care of processing the signal. 
The program will just have to periodically check the flag to know if any response is required.

2. Only use async-signal-safe functions in handlers

The signale manual page maintains a list of safe functions to use in signal handlers. Let’s take note that most of the 
popular functions like printf and even exit are not on this list! This also means that we might need to reconsider our 
example in the previous section

5. Declare shared global variables as volatile

If the handler updates a global variable that the main program reads from time to time, the compiler might think 
that the main program never updates the variable. For optimization’s sake, the compiler might choose to cache it, 
which means that the main program might never see the updated value. The keyword volatile tells to the compiler 
never to cache the variable.
------------------------------------------------------------------------------
## BUILT IN COMMANDS
#include <stdio.h>
#include <unistd.h>

void ft_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}
Uses getcwd() to get the current directory.
Prints the result like the real pwd command.
No forking (runs directly in the main process).
----------------------------------------------------------------------------

## tcsetattr 
stands for "Terminal Control Set Attributes" — it is used to configure terminal settings, such as input modes, output processing, and control flags.
#include <termios.h>

int tcsetattr(int fildes, int optional_actions,
	const struct termios *termios_p);
----------------------------------------------------------------------------
Canonical Mode vs. Non-Canonical Mode in the Terminal
The terminal operates in two modes:

Canonical Mode (Default)

Input is line-buffered (processed after pressing Enter).
Supports line editing (Backspace, Ctrl+U, etc.).
Example: When typing in the shell, you can edit your command before pressing Enter.
Non-Canonical Mode

Input is character-buffered (processed immediately, without Enter).
No built-in line editing.
Used for interactive programs like games or keypress detection (e.g., getch() behavior).
----------------------------------------------------------------------------

Execution means running the parsed command. This includes:

Built-ins (cd, echo, pwd, export, unset, env, exit)
Forking processes (ls, grep, cat)
Handling pipes (|) and redirections (>, <)
Summary
Stage	What It Does
Parsing	Tokenizes input, handles quotes, redirections, pipes, and builds execution structure.
Execution	Runs built-ins, forks processes, manages pipes and redirections.
 Parsing

Tokenizing (strtok, malloc)
Handling operators (|, ;, &&)
Expanding environment variables ($VAR)
Checking syntax errors
Creating a tree structure for command execution
🔹 Execution

Running built-in functions
Forking child processes
Handling file descriptors (dup2())

Environment variables (i.e. $USER or $VAR) that expand to their values.
$? expands to the exit status of the most recently executed foreground pipeline.
User keyboard signals:
ctrl-c displays a new prompt line.
ctrl-d exits minishell
ctrl-\ does nothing
However, Minishell does not support \, ;, &&, ||, or wildcards.
-------------------------------------------------------
CHDIR 
-----------------------------------------------------
cd	Go to $HOME
cd ~	Same as above
cd /path	Go to absolute path
cd relative/path	Move to relative path
cd -	Go to previous directory ($OLDPWD)
cd ..	Go up one directory
cd .	Stay in the current directory
cd ~/folder	Go to "folder" inside your home directory

$HOME → Default when you type cd
$OLDPWD → Used for cd -
$PWD → Updated to show the new path


✅ You only need to handle:
cd some/folder → relative path
cd /home/user → absolute path
❌ You do not need to handle:
cd (no arguments) → would go to $HOME in real bash
cd ~ → would expand to $HOME
cd - → would go to $OLDPWD

Command	Handle?	Why
cd folder	✅ Yes	relative path
cd ../dir	✅ Yes	relative path
cd /usr/bin	✅ Yes	absolute path
❌ What You Can Skip:
Command	Handle?	Reason
cd	❌ No	$HOME not required
cd ~	❌ No	tilde expansion not required
cd -	❌ No	$OLDPWD not required

!! todo !! checks on chdir:
 Run a command such as "$> cd /absolute/path/of/your/choice",
then run the following command "$> /bin/pwd". /bin/pwd
must confirm that the current folder was updated.
- Run a command such as "$> cd relative/path/of/your/choice",
then run the following command "$> /bin/pwd". /bin/pwd
must confirm that the current folder was updated.
- Run the following command "$> cd", then run "$> /bin/pwd".
/bin/pwd must confirm that the current folder is the
user's home folder.
- Run the following command "$> cd -", then run "$> /bin/pwd".
/bin/pwd must confirm that the current folder is the
folder relative/path/of/your/choice used before.
- Run the following command "$> cd ~/path/of/your/choice",
then run "$> /bin/pwd". "$> /bin/pwd". /bin/pwd must
confirm that the current folder was updated.
------------------------------------------------
!! NB !!
------------------------------------------------
Key Directories in Linux (WSL):
Path	Meaning
/home	User home folders
/etc	Config files
/bin, /usr/bin	System commands
/var	Logs, temp data, services
/mnt/c	Access to Windows C:\
-------------------------------------------------------------------
Type		Stays in shell?	Passed to programs?		Shown by env?
VAR=value	✅ Yes			❌ No					❌ No
export VAR	✅ Yes			✅ Yes					✅ Yes
-------------------------------------------------------------------
write vs printf in C:

write (low-level):

Comes from <unistd.h>

Writes raw bytes to a file descriptor.

Syntax: write(fd, buffer, count);

No formatting. Faster. Used in system programming.

printf (high-level):

Comes from <stdio.h>

Writes formatted output to stdout.

Syntax: printf("Value: %d\n", x);

More convenient. Internally uses write.

Example:

c
Copy
Edit
write(1, "Hello\n", 6);		  // raw output
printf("Hello\n");			  // formatted output
==============================================================================



