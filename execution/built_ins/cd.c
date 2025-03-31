#include "../../includes/minishell.h"
#define CWD_MAX 1024

/*
cd
Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
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

int do_cd(char **argv, t_env *env)
{
	char cwd[CWD_MAX];
	char *result = NULL;
	char *oldpwd = get_env_value(env, "PWD");
	printf("OLDPWD:: %s\n", oldpwd);

	if (!argv[1])
	{
		result = ft_strdup(get_env_value(env, "HOME"));
		if (!result)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		printf("CD:: %s\n", result);
	}
	else if (argv[1][0] == '~') // do check for validpathrubbish case
	{
		char *home = get_env_value(env, "HOME");
		if (!home) {
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		char *rest = argv[1] + 1;
		result = ft_strjoin(home, rest); // malloc check?? TODO
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
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
		result = ft_strdup(argv[1]);

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

/*
PWD=/mnt/c/Users/petya.katsarova/OneDrive - CGI/Desktop/minishell_unstoppable
!! NB !!
oLDPWD should only appear after the first cd, and only if PWD existed before. in our program: we start minishell with the original envp from your shell, and that includes OLDPWD. TODO: do i need to do sth abt it?

if no argv[1] or argv[1] starts with "~":
    replace ~ with get_env_path(env, "HOME")
elif argv[1] starts with "/":
    use as absolute path
else:
    use as relative path from current cwd
But in reality, you don’t need to split those cases. You can just ft_strdup(argv[1]) and pass to chdir() — it works for both.

WSL1 uses drvfs, which can confuse POSIX APIs like getcwd()

Long OneDrive paths or symlinks can sometimes confuse WSL's path resolution
*/