// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   unset.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2025/04/08 19:34:04 by pekatsar      #+#    #+#                 */
// /*   Updated: 2025/04/08 19:34:10 by pekatsar      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// t_env	*delete_env_var(char *key, t_env *env_struct)
// {
//     t_env	*new_env;
//     size_t	i = 0, j = 0, env_size = 0;

//     while (env_struct[env_size].key)
//         env_size++;
//     new_env = malloc(sizeof(t_env) * env_size);
//     if (!new_env)
//         return (NULL);

//     while (i < env_size)
//     {
//         if (ft_strncmp(env_struct[i].key, key, ft_strlen(key) + 1) != 0)
//         {
//             new_env[j].key = ft_strdup(env_struct[i].key);
//             new_env[j].value = ft_strdup(env_struct[i].value);
//             new_env[j].exported = env_struct[i].exported;
//             if (!new_env[j].key || (env_struct[i].value && !new_env[j].value))
//                 return (free(new_env), NULL);
//             j++;
//         }
//         else
//         {
//             free(env_struct[i].key);
//             free(env_struct[i].value);
//         }
//         i++;
//     }
//     new_env[j].key = NULL;
//     new_env[j].value = NULL;
//     new_env[j].exported = 0;
//     free(env_struct);
//     return (new_env);
// }

// int	do_unset(char **input_args, t_env *env_struct)
// {
//     size_t	i = 1;
//     int		status = EXIT_SUCCESS;

//     if (!input_args || !env_struct)
//         return (EXIT_FAILURE);

//     while (input_args[i])
//     {
//         if (!input_args[i] || !*input_args[i])
//         {
//             i++;
//             continue;
//         }
//         t_env *new_env = delete_env_var(input_args[i], env_struct);
//         if (!new_env)
//             status = EXIT_FAILURE;
//         else
//             env_struct = new_env;
//         i++;
//     }
//     return (status);
// }
