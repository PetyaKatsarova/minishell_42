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
