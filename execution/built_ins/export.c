
#include "../../includes/minishell.h"

int	do_export(char **input_args, t_env_list *env_struct)
{
	// size_t		i;
	// char		**export_args;
	t_env_list	*sorted_env;

	if (input_args[1])
	{
		// updated curr env_struc
	}
		sorted_env = sort_env(env_struct);
	if (!sorted_env)
		err_malloc(NULL, "minishell: sorted env-struct failed");
	print_env_export(sorted_env);
	free_t_env(sorted_env);
	return (EXIT_SUCCESS);
}

/*
In most shells (like Bash), _ is a special variable that holds the last argument of the last executed command or the absolute path of the current shell or script.
When you run a shell or execute a command, _ is updated to reflect the path of the shell binary or the last executed command.
In this case, _ is set to the path of your minishell binary:
"/home/pekatsar/Desktop/minishell_42/./minishell".
*/
