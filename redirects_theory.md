1. output redirect >
===============================

ls -l >> newf ✅
ls > newfile ✅
ls >> bla <ls >> bla < bla ✘

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





