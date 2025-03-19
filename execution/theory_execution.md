Built-in commands (echo, cd, pwd, export, unset, env, exit) must not use execve because they don't spawn a new process.

User keyboard signals:
ctrl-c displays a new prompt line.
ctrl-d exits minishell
ctrl-\ does nothing
Minishell does not support \, ;, &&, ||, or wildcards.

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

TTY     Value	            Meaning
pts/0	Pseudo-terminal     (process running inside a terminal emulator like bash, ssh, tmux).
hvc0	Hypervisor Console  (used by WSL, virtual machines, or cloud instances).
?	    No terminal         (background system process, daemon, or service).

SessionLeader → Manages a login session.
Relay(607) → A relay process handling communication.

Git Bash is not real Bash, it’s MinGW (Minimalist GNU for Windows).
MinGW lacks Linux-style process management, so pidof doesn't exist.

echo "PID = $$; PPID = $PPID"
$$ → Current shell’s Process ID (PID).
$PPID → Parent Process ID (PPID).
-----------------------------------------

$ pidof bash //systemd
$ pidof top
$ pidof pidofCode language: Shell Session (shell)