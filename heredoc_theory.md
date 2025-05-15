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

Before forking, parent:

Traverses tree

For each <<, collects heredoc input

Stores it (e.g. redir->heredoc_str)

Later, in child:

apply_heredoc() just redirects from saved string

Your current flow:
Child forks first
Then asks for heredoc input
But pipes, files, or order may already be broken → undefined behavior
Bash does all input before forking, so:
All heredoc prompts show first
No pipe/file conflict
Works even with complex pipelines
So yes, change flow:
Collect in parent → use in child.
===============================================
Iterate tree:
Traverse all command nodes left-to-right (go_first_cmd → go_next_cmd).

Within each command node:
Go through redirection list (redir = go_next_redir(cmd)).

For each redirection:
If it's HEREDOC, do:

Prompt user input (readline("> ") loop until delimiter).

Store full heredoc string in redir->heredoc_str.

⚠️ All redir->heredoc_str are filled before any fork/exec.
Setup input/output pipes with dup2.

Apply redirections (apply_redirections()):

For each redirect node:

HEREDOC → Write redir->heredoc_str to temp file, open it, dup2 to STDIN.

> or >> → Open file, dup2 to STDOUT.

Execute command (exec_on_path() or builtin).
Setup input/output pipes with dup2.

Apply redirections (apply_redirections()):

For each redirect node:

HEREDOC → Write redir->heredoc_str to temp file, open it, dup2 to STDIN.

> or >> → Open file, dup2 to STDOUT.

Execute command (exec_on_path() or builtin).
PIPE
├─ CMD: cat
│  └─ REDIR: HEREDOC 'a', OUTPUT > a
├─ CMD: cat
│  └─ REDIR: HEREDOC 'b', APPEND >> a
└─ CMD: cat a b
First redir->heredoc_str = "content for a"

Second redir->heredoc_str = "content for b"

Stored in separate t_node *redir linked lists


