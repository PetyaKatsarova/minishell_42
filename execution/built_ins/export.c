
#include "../../includes/minishell.h"

/* perror the msg, frees t_env cpy and exits_failure */
/**
 * 1.export var = hello' should print a syntax error and return the prompt. In our minishell, it causes valgrind errors and exports both 'var' and 'hi' as variables without assigning a value to either.
 * 
2.Each exported variable causes definitely lost leaks.
3.'export var=hi=hi=hi=' should export a variable with name 'var' and value 'hi=hi=hi='. Our minishell currently exports the variable 'var' with value 'hi'. The rest of the string is thrown away. This means our variable cannot store any value containing an '='
4. Another example: '2 + 2 = 4' is truncated to '2 + 2 '.
 5.According to the bash reference, variable names may only contain digits, letters (lower- and uppercase), and underscores. This is not super important, however.

 1. c
 */
int err_malloc(t_env_list *cpy, char *msg)
{
	perror(msg);
	if (cpy)
		free_t_env(cpy);
	exit(EXIT_FAILURE);
}

static int is_valisd_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

static void	parse_key_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_substr(arg, 0, i);
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
	else
		*value = NULL;
}

static int	has_space_around_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i > 0 && arg[i - 1] == ' ')
		return (1);
	if (arg[i] == '=' && arg[i + 1] == ' ')
		return (1);
	return (0);
}

static int	append_replace_envvar(char *argv, t_env_list *env_struct)
{
	char	*key;
	char	*value;

	if (has_space_around_equal(argv))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	parse_key_value(argv, &key, &value);
	if (!key || !is_valid_identifier(key))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	set_env_value(env_struct, key, value);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
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
			if (append_replace_envvar(input_args[i], env_struct) == EXIT_FAILURE)
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
