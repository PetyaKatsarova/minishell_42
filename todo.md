1. ./minishel in ./minishel when ctr+c: exit only the current one
: make sure have func in minishel: if child proces in minishell ignore all signals!

2. undefined behavior in:
	a.) echo -n -n bla, echo -n -n2 bla, echo -n2 -nnn bla
	b.) exit ....

3. export:
	a. if readline returns bla, save in sorted env last, exported=0
	b. if readline returns export bla: check if bla, exists, if bla has val, replace, otherwise leave empty: both cases set export=1, if bla doesnt exist: append at the end of sorted_env, if export bla=, output is: bla=""

4. deal with $var, $?, $$(maybe not needed?): parsing person to do?

5. update SHLVL accordingly on every run of shell in shell and exitting

6. Running several commands with pipes leads to invalid attempts to close FDs that have already been closed. Other FDs are left open.


https://github.com/froz42/funcheck : check all mallocs
https://github.com/froz42/funcheck.git

signals for heredoc: ctr+c, d , \ handles

cat <<EOF >file
heredoc> gsa
heredoc> fsafsaf
heredoc> EOF

fd=3 
unlink

close
cat <(heredoc-file) >file

save_in = dup(stdin_fileno);

dup2(oldfd, save_in);
close(save_in);

// TO CHECK how bash does ti

strace -f bash -c $'cat << EOF
ADSFDSAF
ASDFDS
EOF
'

signals: shell in shell ....

systemd-run --user --collect --pty -p TaskMax=1 /bin/bash
dprintf() with fd

stuck:
handle_cmds(tree, env_struct_lst, cmd_node, exit_status);

f0r6s9% valgrind -q --track-fds=yes --trace-children=yes ./minishell
minihell$ bla | echo yes | ls | grep main

✅
terminal: when writing to the terminal the first line will be overwritten when input exceeds line length
terminal: when using arrow keys to go up and down in the history several times, the printing of the history often gets corrupted (happens especially with long commands) --- TODO -----------------------------------------
redirs: so far, input consisting only of redirs (no command) is not handled. bash creates all files in this case (Jan thinks this is defined behavior, we might want to check again)
valgrind: starting at version 3.23 valgrind interprets double closes of file descriptors as errors. (codam does not have an up-to-date version of valgrind, so these errors are not found on school computers). currently, we have double closes of fds when using pipes (always), and with redirs when trying to write to a file without write permission


< cat bla | pwd | grep m

echo b | adf adf asdf | cat < bla | grep a