
#include "../../includes/minishell.h"

/* on export cmd: sort and display all vars with declare -x,
export MYVAR is added at the bottom if the list!
*/

/*
t_env temp = *el1;
el1 is a pointer → it points to a t_env struct
*el1 means: “dereference the pointer → get the actual struct”
So you're copying the whole struct into temp
(if el1 points to [key=USER])
el1	pointer (address)	0x123abc
*el1	the struct itself	{key="USER", value="petya"}
el1->key	shortcut for (*el1).key	"USER"
When you write:
t_env temp = *el1;
You're copying the full struct from address el1 into a local variable temp.
box temp = contents of el1
el1 = contents of el2
el2 = temp
!NB: export and export -p behave the same
*/

/*
TODO ONCE PARSER IS READY:
1. if existing env var=bla, replace value
2. if not existing var=bla, not exported: add to env, set exported=0
3. if exported: print sorted env but all next exported vars append last exported on the bottom
in env print as it comes from env, but in export: all exported append at the end, not sorted
*/
// if contains export: if exists, replace if not add, change size of list and check capacity... 

/*
Handles the `export` built-in command:
1. If no arguments, prints all variables in `declare -x` format.
2. If arguments are provided:
   - Adds new variables or updates existing ones.
   - Handles `VAR=value`, `VAR+=value`, and `export VAR`.
   - Validates variable names and prints errors for invalid ones.
*/

static int parse_export_arg(char *arg, char **result, size_t i)
{
	size_t len;

	len = i;
	if (arg[i - 1] == '+')
	{
		result[0] = "+";
		len = i - 1;
	}
	else
		result[0] = NULL;

	result[1] = ft_strndup(arg, len);
	if (!result[1])
		return (0);

	if (arg[i + 1])
	{
		result[2] = ft_strdup(arg + i + 1);
		if (!result[2])
			return (0);
	}
	else
		result[2] = NULL;

	return (1);
}

static size_t	export_check_chars(char *arg)
{
	size_t	i;

	i = 1;
	// Check if the first character is valid (must be a letter or '_')
	if (ft_isdigit(arg[0]) || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);

	// Check the rest of the characters
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i); // Return the position of '='
		if (!(ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_'))
		{
			if (arg[i] == '+' && arg[i + 1] == '=')
				return (i + 1); // Return the position of '+='
			return (0); // Invalid character
		}
		i++;
	}
	return (0); // No '=' or '+=' found
}

static void	add_new_env_var(t_env_list *env_struct, char *key, char *value)
{
	t_env	*new_vars;
	size_t	i;

	if (env_struct->size >= env_struct->capacity)
	{
		env_struct->capacity *= 2;
		new_vars = malloc(sizeof(t_env) * env_struct->capacity);
		if (!new_vars)
			return ; // TODO: handle error ??
		i = 0;
		while (i < env_struct->size)
		{
			new_vars[i].key = env_struct->vars[i].key;
			new_vars[i].value = env_struct->vars[i].value;
			new_vars[i].exported = env_struct->vars[i].exported;
			i++;
		}
		free(env_struct->vars);
		env_struct->vars = new_vars;
	}
	env_struct->vars[env_struct->size].key = ft_strdup(key);
	env_struct->vars[env_struct->size].value = ft_strdup(value);
	env_struct->vars[env_struct->size].exported = 1;
	env_struct->size++;
}

static char	**check_export_arg(char *arg)
{
	char	**result;
	size_t	i;

	result = ft_calloc(3, sizeof(char *));
	if (!result)
		return (NULL); // todo: handle error
	i = export_check_chars(arg);
	if (i == 0)
	{
		free(result);
		if (print_builtin_error("export", arg, "not a valid identifier") == EXIT_FAILURE)
			return (NULL);
	}
	if (!parse_export_arg(arg, result, i))
	{
		free(result[1]);
		free(result[2]);
		free(result);
		return (NULL);
	}
	return (result);
}

static void	update_env_export(char **export_args, t_env_list *env_struct)
{
	size_t	i;
	char	*val;

	i = 0;
	val = ft_strjoin(export_args[1], "=");
	if (!val)
		return ; // handle err: todo
	while (i < env_struct->size)
	{
		if (!ft_strncmp(val, env_struct->vars[i].key, ft_strlen(val)))
		{
			if (export_args[0]) // Append to existing value
				env_struct->vars[i].value = ft_strjoin(env_struct->vars[i].value, export_args[2]);
			else // Replace existing value
				env_struct->vars[i].value = ft_strdup(export_args[2]);
			free(val);
			return ;
		}
		i++;
	}
	// Add new var if not found
	add_new_env_var(env_struct, export_args[1], export_args[2]);
	free(val);
}

/*
Assuming input_args[0]="export"	
*/
int	do_export(char **input_args, t_env_list *env_struct)
{
	size_t		i;
	char		**export_args;
	t_env_list	*sorted_env;

	if (!input_args[1])
	{
		sorted_env = sort_env(env_struct);
		if (!sorted_env)
			err_malloc(NULL, "minishell: sorted env-struct failed");
		print_env_export(sorted_env);
		free_t_env(sorted_env);
		return (EXIT_SUCCESS);
	}
	// i = 1;
	// while (input_args[i])
	// {
	//	 export_args = check_export_arg(input_args[i]); // here todo
	//	 if (!export_args)
	//		 return (EXIT_FAILURE);
	//	 update_env_export(export_args, env_struct); // todo
	//	 free(export_args[1]);
	//	 free(export_args[2]);
	//	 free(export_args);
	//	 i++;
	// }
	return (EXIT_SUCCESS);
}
