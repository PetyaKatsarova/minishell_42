cat <<a >a | cat <<b >>a | cat a

Expected Bash behavior:
Bash sets up all heredocs first, then pipes, then runs commands in parallel.
Redirections go to files.
Pipes pass stdout only, not side effects (like writing files).
Order of execution may lead to race conditions or partial reads.

The missing 22 is likely due to timing/buffering or how redirections are flushed.
=================================
SIGNALS
=================================
extern: tells compiler g_signum is defined elsewhere (not here).

volatile: tells compiler: don’t optimize — value may change anytime (e.g., by signal).

sig_atomic_t: safe int type for signal access.
✅ CTRL-C (SIGINT)
Interactive mode: show a new prompt on a new line

Should not exit

Should not kill the shell

Must set exit code to 130

✅ CTRL-D
Means: EOF (readline() returns NULL)

Shell must exit gracefully

Free memory, close FDs