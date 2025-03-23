/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:56:22 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/20 16:00:12 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"
#define CWD_MAX 1024

static char *get_env_path(char **env, const char *key)
{
    int i = 0;
    size_t key_len = ft_strlen(key);

    while (env[i])
    {
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (env[i] + key_len + 1);
        i++;
    }
    return (NULL);
}

static void update_path(char **env, char *key, char *val)
{
    int i = 0;
    size_t key_len = ft_strlen(key);
    char *temp = ft_strjoin(key, "=");
    char *path;

    if (!temp) return;
    path = ft_strjoin(temp, val);
    free(temp);
    if (!path) return;
    while (env[i])
    {
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
        {
            free(env[i]);
            env[i] = path;
            return;
        }
        i++;
    }
    free(path);
}

static void print_error(const char *msg)
{
    write(2, "cd: ", 4);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
}

int do_cd(char **argv, char **env)
{
    char cwd[CWD_MAX];
    char *result = NULL;

    // Handle: cd or cd ~
    if (!argv[1] || ft_strncmp(argv[1], "~", 1) == 0)
    {
        char *home = get_env_path(env, "HOME");
        if (!home)
            return (print_error("HOME not set"), 1);
        result = ft_strdup(home); // ✅ duplicated, safe to free
    }
    // Handle: cd -
    else if (ft_strncmp(argv[1], "-", 1) == 0)
    {
        char *oldpwd = get_env_path(env, "OLDPWD");
        if (!oldpwd)
            return (print_error("OLDPWD not set"), 1);
        result = ft_strdup(oldpwd);
    }
    // Handle: cd ~/...
    else if (ft_strncmp(argv[1], "~/", 2) == 0)
    {
        char *home = get_env_path(env, "HOME");
        if (!home)
            return (print_error("HOME not set"), 1);
        result = ft_strjoin(home, argv[1] + 1);
    }
    // Handle: cd path
    else
        result = ft_strdup(argv[1]);

    if (!result)
        return (print_error("Memory allocation failed"), 1);

    // Update OLDPWD before changing dir
    if (getcwd(cwd, CWD_MAX))
        update_path(env, "OLDPWD", cwd);

    // Try changing dir
    if (chdir(result) != 0)
    {
        write(2, "cd: ", 4);
        write(2, result, ft_strlen(result));
        write(2, ": No such file or directory\n", 29);
        free(result);
        return (1);
    }

    // Update PWD after change
    if (getcwd(cwd, CWD_MAX))
        update_path(env, "PWD", cwd);

    free(result);
    return (0);
}

/*
chdir() changes the current working directory of the calling process to the directory specified in path.
On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
       Depending on the filesystem, other errors can be returned.  The more general errors for chdir() are listed below:
       EACCES Search permission is denied for one of the components of path.  (See also path_resolution(7).)
       EFAULT path points outside your accessible address space.
       EIO    An I/O error occurred. etc
              The current working directory is the starting point for interpreting relative pathnames (those not starting with '/').

       A  child  process  created via fork(2) inherits its parent's current working directory.  The current working directory is left un‐
       changed by execve(2).

           if (chdir("..") == 0) {
        getcwd(cwd, sizeof(cwd));
        printf("Changed directory: %s\n\n", cwd);
    } else {
        perror("chdir failed");
        return 1;
    }
*/

