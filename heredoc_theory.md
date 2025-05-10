Quoted Delimiters: Remember that quoting the delimiter affects variable expansion within the heredoc.

Multiple Heredocs: Commands can have multiple heredocs; ensure your parser and executor handle them sequentially.

Nested Heredocs: While rare, be cautious of scenarios where heredocs might appear within other heredocs.

Signal Handling: Properly handle interruptions during heredoc input to prevent resource leaks or undefined behavior.

  cat <<EOF
  Hello World
  EOF
=========================
  var="World"
  cat <<EOF
  Hello $var
  EOF
================================

  cat <<'EOF'
  Hello $var
  EOF
==========================
#!/bin/bash

cat << EOF | base64 -d
SGVsbG8KV29ybGQK
EOF
Copy
Alternatively, use redirect notation to achieve the same result:

#!/bin/bash

(base64 -d) < cat << EOF
SGVsbG8KV29ybGQK
EOF


=================================
cat << A << B
first
A
second
B

Expected output:

second
====================================================
grep foo << A | cat << B
foo from left
A
bar from right
B
foo from left
bar from right
=====================================================
This is syntactically allowed, but heredocs can't contain actual inner heredocs. The inner << is just plain text:
cat << EOF
inside text
<< NESTED
more text
EOF
Expected output:

inside text
<< NESTED
more text
Your minishell must treat << inside a heredoc body as plain text.

======================================================
Interrupted Input:
Start a heredoc and press Ctrl+C to ensure it handles the interruption gracefully.

EOF Handling:
Start a heredoc and press Ctrl+D before entering the delimiter to test EOF behavior.
=====================================





A heredoc lets you feed multiline input to a command directly in the shell, until a delimiter word is found.

cat << EOF
hello
world
EOF

hello
world


→ Everything typed between <<DELIMITER and the final DELIMITER becomes stdin for the command.


------------------ TEST CASES -----------------------------------------------------------------------
minihell$ wc -l <<s
> sf
> sadf
> adsf
> s
3

works with: wc, grep, grep, 
minihell$ pwd << a
> adfds
> a
/home/pekatsar/Desktop/minishell_42

cat << EOF | cat
line 1
line 2
EOF
Output: line 1\nline 2

grep foo << END | cat
foo bar
baz
END

cat << X | grep hello
hello world
bye
X

Multiple heredocs (only the last one counts) ---- TODO..... BUG
cat << A << B | cat
ignored
A
used
B
Output: used

cat << X | cat
X

cat << X | grep test | wc -l
test line
X

