/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:17:10 by pekatsar          #+#    #+#             */
/*   Updated: 2025/03/24 18:24:01 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// sudo apt-get install libreadline-dev

static int handle_readline(char **env)
{
	while (1)
	{
		char *input = readline("\033[1;34mminihell$\033[0m ");

		if (!input) // handle CTR+D
		{
			printf("exit with no input collected.\n");
			return (EXIT_FAILURE); // NEED TO CLEAR ALL MALLOCS 
		}
		if (*input) // DO I NEED hte if?
			add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			return (0); // free all later
		}
		else
		{
			if (ft_strncmp(input, "pwd", 3) == 0)
				get_pwd();
			else if (ft_strncmp(input, "cd", 2) == 0)
			{
				char **args = ft_split(input, ' ');
				do_cd(args, env);
				int i = 0;
				while (args[i])
				{
					free(args[i]);
					i++;
				}
				free(args);
			}
			else if (ft_strncmp(input, "env", 3) == 0) // just for testing
			{
				int i = 0;
				while (env[i++])
					printf("handle_readline: %s\n", env[i]);
			}
			else
			{
				printf("under construction. but unstoppable ....\n");
				system(input); // not allowd funcs: for testing only
			}
		}
		free(input);
	}
	return (0);
}

static char **copy_env(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    char **copy = malloc(sizeof(char *) * (i + 10)); // if we need OLDPWD addition to env and more..
    if (!copy)
        return NULL;
    for (int j = 0; j < i; j++)
        copy[j] = ft_strdup(envp[j]);
    copy[i] = NULL;
    return copy;
}

static void free_env(char **env)
{
    int i = 0;
    while (env[i])
        free(env[i++]);
    free(env);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main(int argc, char **argv, char **env) {
	(void) argc;
	(void) argv;
	char **envp = copy_env(env);
	handle_readline(envp);
	free_env(envp);
    return (0);
}
