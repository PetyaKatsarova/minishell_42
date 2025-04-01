/*
echo -n // -n dont output the trailing newline, echo - display a line of text
Execute the echo command with or without arguments, or the -n option.
Repeat multiple times with different arguments.
*/

#include "../../includes/minishell.h"

/*
echo -n -nnnnnnnnnnnnnn bla: handle TODO
*/

static int only_n(char *str)
{
    int i = 1; // in next func is checked that str[0] = '-'

    while (str[i])
    {
        if (str[i] != 'n')
            return (0); // not only ns
        i++;
    }
    return (1);
}

int do_echo(char **argv)
{
    int i = 1;
    int new_line = 1;

    if (argv[1] && ft_strncmp(argv[1], "-n", 1) == 0 && only_n(argv[1]) == 1)
    {
        new_line = 0;
        i++;
    }
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i+1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
    return (EXIT_SUCCESS); // 0
}
