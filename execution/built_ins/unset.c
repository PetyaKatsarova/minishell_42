#include "../../includes/minishell.h"

void do_unset(char **input_args, t_env *env_struct)
{
	int i = 1;

	while (input_args[i])
	{
		int j = 0;
        int key_len = 0;
		while (env_struct[j].key)
		{
            key_len = ft_strlen(env_struct[j].key);
			if (ft_strncmp(env_struct[j].key, input_args[i], key_len) == 0 &&
    env_struct[j].key[key_len] == '\0' &&
    input_args[i][key_len] == '\0')
			{
				free(env_struct[j].key);
				free(env_struct[j].value);

				// Shift the rest left
				while (env_struct[j + 1].key)
				{
					env_struct[j] = env_struct[j + 1];
					j++;
				}
				// Null-terminate the new end
				env_struct[j].key = NULL;
				env_struct[j].value = NULL;
				env_struct[j].exported = 0;
				break;
			}
			j++;
		}
		i++;
	}
}
