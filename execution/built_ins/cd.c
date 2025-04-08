#include "../../includes/minishell.h"
#define CWD_MAX 1024

/*
cd
Use the command cd to move the working directory and check if you are in the right directory with /bin/ls: !!NB!! /bin/ls is the actual binary of the ls command — the one that lists files.
Why use /bin/ls? same result as ls
It bypasses aliases or shell functions, running the real system ls directly.
Useful when:
You want raw ls behavior
Your shell has an alias like alias ls='ls --color=auto'

Repeat multiple times with working and not working cd
Also, try '.' and '..' as arguments.
pwd
Use the command pwd.
Repeat multiple times in different directories.
Relative Path
Execute commands but this time use a relative path.
Repeat multiple times in different directories with a complex relative path (lots of ..).
Environment path
Execute commands but this time without any path (ls, wc, awk and so forth).
Unset the $PATH and ensure commands are not working anymore.
Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in
order from left to right.
*/

// for each command check if has $ and if so: replace key
int do_cd(char **input_args, t_env_list *env)
{
	char cwd[CWD_MAX];
	char *result = NULL;
	char *oldpwd = get_env_value(env, "PWD");
	//printf("OLDPWD:: %s\n", oldpwd);

	if (too_many_args(input_args))
	{
		print_builtin_error("cd", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	if (!input_args[1])
	{
		result = ft_strdup(get_env_value(env, "HOME"));
		if (!result)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		printf("CD:: %s\n", result);
	}
	else if (input_args[1][0] == '~')
	{
		char	*home = get_env_value(env, "HOME");
		char	*rest;
		
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		rest = input_args[1] + 1; // everything after '~'

		// if it's just "~", cd to HOME
		if (rest[0] == '\0')
			result = ft_strdup(home);
		else if (rest[0] == '/') // "~/folder" case
			result = ft_strjoin(home, rest); // result = HOME + /folder
		else
		{
			// unsupported like "~username" → treat as literal path
			result = ft_strdup(input_args[1]);
		}
		if (!result) // do i need this?
			return (EXIT_FAILURE); // exit failure strategy: what num?
	}
	else if (input_args[1][0] == '-' && input_args[1][1] == '\0')
	{
		char *old = get_env_value(env, "OLDPWD");
		if (!old)
		{
            // todo: check management in bash
			fprintf(stderr, "minishell: cd: OLDPWD not set\n");
			return (EXIT_FAILURE);
		}
		// printf("%s\n", old); // print the path being switched to
		result = ft_strdup(old);
	}
	else
		result = ft_strdup(input_args[1]);

	if (!result || chdir(result) != 0)
	{
		perror("cd");
		free(result);
		return (EXIT_FAILURE);
	}

	if (oldpwd)
		set_env_value(env, "OLDPWD", oldpwd);
	if (getcwd(cwd, CWD_MAX))
		set_env_value(env, "PWD", cwd);

	free(result);
	return (EXIT_SUCCESS);
}
