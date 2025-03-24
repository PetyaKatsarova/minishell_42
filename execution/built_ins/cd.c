#include "../../includes/minishell.h"
#define CWD_MAX 1024

static char *get_env_path(char **env, const char *key)
{
    int     i = 0;
    size_t  key_len = ft_strlen(key);

    while (env[i])
    {
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
        {
            return (env[i] + key_len + 1);
        }
        i++;
    }
    return (NULL);
}

static void update_path(char **env, char *key, char *val)
{
    int     i = 0;
    size_t  key_len = ft_strlen(key);
    char    *temp = ft_strjoin(key, "=");
    char    *path;

    if (!temp)
        return; // need to free sth??
    path = ft_strjoin(temp, val);
    free(temp);
    if (!path)
    {
        printf("error in joining path, update_path\n");
        return;
    }
    
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
    printf("first_time_oldpwd: %s\n", path);
    env[i] = path;
    env[i + 1] = NULL;
}

int do_cd(char **argv, char **env)
{
    char cwd[CWD_MAX];
    char *result = NULL;
    char *oldpwd = get_env_path(env, "PWD");

    if (!argv[1])
    {
        printf("no argv[1], wy??: %s\n", argv[1]); // TOOD: remove
        result = ft_strdup(get_env_path(env, "HOME"));
    }
    else if (argv[1][0] == '~')
    {
        char *home = get_env_path(env, "HOME");
        char *rest = argv[1] + 1;
        result = ft_strjoin(home, rest); // handles "~/subdir"
    }
    else
        result = ft_strdup(argv[1]); // absolute or relative path
    if (!result || chdir(result) != 0)
    {
        perror("cd\n");
        free(result);
        return (EXIT_FAILURE);
    }
    if (oldpwd)
        update_path(env, "OLDPWD", oldpwd);
    if (getcwd(cwd, CWD_MAX))
        update_path(env, "PWD", cwd);
    free(result);
    return (EXIT_SUCCESS);
}

/*
!! NB !!
oLDPWD should only appear after the first cd, and only if PWD existed before. in our program: we start minishell with the original envp from your shell, and that includes OLDPWD. TODO: do i need to do sth abt it?

if no argv[1] or argv[1] starts with "~":
    replace ~ with get_env_path(env, "HOME")
elif argv[1] starts with "/":
    use as absolute path
else:
    use as relative path from current cwd
But in reality, you don’t need to split those cases. You can just ft_strdup(argv[1]) and pass to chdir() — it works for both.

WSL1 uses drvfs, which can confuse POSIX APIs like getcwd()

Long OneDrive paths or symlinks can sometimes confuse WSL's path resolution
*/