/*
Input	What to do
VAR=value	Add to list (not exported)
export VAR	Mark as exported (even if it had no value yet)
export VAR=hi	Add/update and mark exported
env	Print only exported + with values
export	Print all (with or without value), format as declare -x

VAR1=hello          # just stored, not exported
export VAR1         # now it's exported
env                 # now shows VAR1=hello
export              # shows declare -x VAR1="hello"

       This  manual  page  is part of the POSIX Programmer's Manual.  The Linux
       implementation of this interface may differ (consult  the  corresponding
       Linux  manual  page for details of Linux behavior), or the interface may
       not be implemented on Linux.

NAME
       export — set the export attribute for variables

    Export environment variables, create new ones and replace old ones.
    Check the result with env.
    Command	Sorted?	Shows vars without values?
*/
#include "../../includes/minishell.h"

// on export cmnd: sort and display all vars with declare -x,
// export MYVAR is added at the bottom if the list!



/*
t_env temp = *el1;
el1 is a pointer → it points to a t_env struct
*el1 means: “dereference the pointer → get the actual struct”
So you're copying the whole struct into temp

Name	What it is	Example (if el1 points to [key=USER])
el1	pointer (address)	0x123abc
*el1	the struct itself	{key="USER", value="petya"}
el1->key	shortcut for (*el1).key	"USER"
🔸 When you write:
t_env temp = *el1;
You're copying the full struct from address el1 into a local variable temp.
box temp = contents of el1
el1 = contents of el2
el2 = temp
*/

//case 1: call export allone: display sorted env, this is for array, need to change for linked list

static t_env *sort_exported_env(t_env *env_struct)
{
    t_env   *result;
    int     struct_len, i, j;

    struct_len = 0;
    while (env_struct->key)
        struct_len++;
    result = malloc(sizeof(t_env) * (struct_len + 1));
    if (!result)
    {
        // clean sth?
        perror("err alloc export sort memory.\n"); // todo: add err num for later management
        return (NULL);
    }

    i = 0;
    while (i)
    {
        j = i;
        while (result[j].key)
        {
            //todo
            j++;
        }
        i++;
    }

    return (result);
}