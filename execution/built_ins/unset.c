// /* ************************************************************************** */
// /*																			*/
// /*														::::::::			*/
// /*   unset.c											:+:	:+:			*/
// /*													 +:+					*/
// /*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
// /*												   +#+					  */
// /*   Created: 2025/04/08 19:34:04 by pekatsar	  #+#	#+#				 */
// /*   Updated: 2025/04/08 19:34:10 by pekatsar	  ########   odam.nl		 */
// /*																			*/
// /* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Move last el in the place of the deleted one, and set last el to NULL
 */
static void delete_env_var(const char *key, t_env_list *env_list)
{
	size_t i = 0;
	size_t len = ft_strlen(key);

	while (i < env_list->size)
	{
		if (ft_strncmp(env_list->vars[i].key, key, len) == 0 && env_list->vars[i].key[len] == '\0')
		{
			free(env_list->vars[i].key);
			free(env_list->vars[i].value);

			env_list->vars[i] = env_list->vars[env_list->size - 1];
			env_list->vars[env_list->size - 1].key = NULL;
			env_list->vars[env_list->size - 1].value = NULL;
			env_list->vars[env_list->size - 1].exported = 0;

			env_list->size--;
			return;
		}
		i++;
	}
}
/**
 * Unset not_existent_var: no error, fails silently like bash
 */
int do_unset(char **input_args, t_env_list *env_struct)
{
	size_t i;

	if (!input_args || !env_struct)
		return (EXIT_FAILURE);

	i = 1; // 0 is cmd unset
	while (input_args[i])
	{
		if (!ft_isalpha(input_args[i][0]) && input_args[i][0] != '_')
			print_builtin_error("unset", input_args[i], "not a valid identifier");
		else
			delete_env_var(input_args[i], env_struct);
		i++;
	}
	return (EXIT_SUCCESS);
}
