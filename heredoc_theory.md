cat <<a >a | cat <<b >>a | cat a

Expected Bash behavior:
Bash sets up all heredocs first, then pipes, then runs commands in parallel.
Redirections go to files.
Pipes pass stdout only, not side effects (like writing files).
Order of execution may lead to race conditions or partial reads.

The missing 22 is likely due to timing/buffering or how redirections are flushed.
=================================