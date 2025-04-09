
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


/*
Assuming input_args[0]="export"	
*/
int	do_export(char **input_args, t_env_list *env_struct)
{
    // size_t		i;
    // char		**export_args;
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

    return (EXIT_SUCCESS);
}
