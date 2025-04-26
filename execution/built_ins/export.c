
#include "../../includes/minishell.h"

/* perror the msg, frees t_env cpy and exits_failure */
int err_malloc(t_env_list *cpy, char *msg)
{
	perror(msg);
	if (cpy)
		free_t_env(cpy);
	exit(EXIT_FAILURE);
}

static	int	append_replace_envvar(char *argv, t_env_list *env_struct)
{
	char		**key_val;

	key_val = ft_split(argv, '=');
	if (!key_val)
	{
		perror("Error in splitting export var.");
		perror ("export: 'badinput': not a valid identifier"); // tood: which to keep
		return (ERROR_ON_SPLIT);
	}
	set_env_value(env_struct, key_val[0], key_val[1]);
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
				return (EXIT_FAILURE);
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
