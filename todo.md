1. ./minishel in ./minishel when ctr+c: exit only the current one
: make sure have func in minishel: if child proces in minishell ignore all signals!

2. undefined behavior in:
	a.) echo -n -n bla, echo -n -n2 bla, echo -n2 -nnn bla
	b.) exit ....