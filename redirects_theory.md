1. output redirect >
===============================

ls -l >> newf ✅
ls > newfile ✅


ls >> bla <ls >> bla < bla ✅
echo bla tra la la > b2 < b3 ✅ ✘ deletes b2 content, get msg: no b3 file 
echo hello > file1 > file2 ✅
ls >> bla < bla2 ✅

==========================
1. ✅
echo hi > output.txt < missing.txt
Expected (Bash):
output.txt is created and empty.
Error: missing.txt: No such file or directory
===============================
2. ✅
echo hi > output.txt < input.txt
Expected:
output.txt created/truncated
Contents of input.txt can be read (if your shell reads it)
=========================================
3. ✅
echo hi > out1.txt < in1.txt < in2.txt
if in1.txt exists but in2.txt does not:
Expected:
out1.txt is created
Error: in2.txt: No such file or directory
No output from echo
====================================
4. ✅
cat < bla | grep la | wc -w > bla2 x
if bla doesnt exits: get msg: no such file or dir bla, bla2 is created if not exists and has 0
========================================



 ✘

< bla2:

Bash tries to open bla2 for reading (stdin redirection).

!!NB!!
Bash runs cmds from left to right, however:
Bash opens all redirection files before executing the command.
If input.txt doesn't exist → error, command not run.
If output.txt doesn't exist → it is created immediately (even if command later fails).

If bla2 does not exist, bash prints:

yaml
Copy
Edit
bash: bla2: No such file or directory
Command is not executed.

>> bla:

This would append stdout to bla, but it never happens if bla2 is missing.

✅ Expected behavior in bash:
If bla2 does not exist, you'll see:
bash: bla2: No such file or directory

✘

ls >> bla <ls >> bla < bla
bash: ls: No such file or directory


================================

minihell: ls: No such file or directory
ls: Bad file descriptor in what cases will get this: waht cmd in shell can invoke 


ChatGPT said:
You’ll see:

yaml
Copy
Edit
minihell: ls: No such file or directory
ls: Bad file descriptor
when both happen:

Your shell can't find ls (e.g., not in $PATH or wrong name):

get_command_path() fails

sets last_exit_status = 127

prints: minihell: ls: No such file or directory

Your shell still tries to execute ls, or sets up its redirections using invalid file descriptors:

for example, < ls treats ls as an input file

file doesn't exist → open() fails → fd = -1

then you call dup2(-1, STDIN_FILENO) → triggers:

bash
Copy
Edit
ls: Bad file descriptor
🧪 Example command that causes this:
bash
Copy
Edit
ls >> out < ls
Assuming no file named ls exists, this leads to:

"No such file or directory" from trying to open ls as input

"Bad file descriptor" if your shell still tries to dup2() or execve() despite the error

✅ Fix:
In your shell:

After any failed open(), do not call dup2() or execve()

Skip execution if redirection setup failed





