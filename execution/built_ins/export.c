
#include "../../includes/minishell.h"

/**
 * if token=export and argv[1] has = and !argv[2]
 * 
 * export var1=bla var2=bla2
 * 
 * Check if key already exists → update value and return.

Check if size >= capacity → return error or handle manually.

Add new t_env entry at size++.

Null-terminate vars[size].key = NULL.



 */

static	int	append_replace_envvar(char *argv, t_env_list *env_struct)
{
	int		i;
	char		**key_val;

	i = 0;
	key_val = ft_split(argv, '=');
	if (!key_val)
	{
		perror("Error in splitting export var.");
		perror ("export: 'badinput': not a valid identifier"); // tood: which to keep
		return (ERROR_ON_SPLIT);
	}
	set_env_value(env_struct, key_val[0], key_val[1]);
	// deal with invalid ...
	free(key_val[0]);
	if (key_val[1])
	free(key_val[1]);
	return (0);
}



int	do_export(char **input_args, t_env_list *env_struct)
{
	int			i;
	t_env_list	*sorted_env;

	i = 1; // 0 is export cmd
	sorted_env = NULL;
	if (input_args[1])
	{
		while (input_args[i])
		{
			if (append_replace_envvar(input_args[i], env_struct) == ERROR_ON_SPLIT)
			{
				return (ERROR_ON_SPLIT);
			}
			i++;
		}
	}
	else
	{
		sorted_env = sort_env(env_struct);
		if (!sorted_env)
			err_malloc(NULL, "minishell: sorted env-struct failed");
		print_env_export(sorted_env);
	}
	free_t_env(sorted_env);
	return (EXIT_SUCCESS);
}

/*
In most shells (like Bash), _ is a special variable that holds the last argument of the last executed command or the absolute path of the current shell or script.
When you run a shell or execute a command, _ is updated to reflect the path of the shell binary or the last executed command.
In this case, _ is set to the path of your minishell binary:
"/home/pekatsar/Desktop/minishell_42/./minishell".
*/
