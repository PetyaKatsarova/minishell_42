#include "../../includes/minishell.h"

/*
add to env struc not exported var, like: bla=blabla
1. readline args: if bla=blabla: add to env struct, set exported=0
2. if export bla=blabla: check if already in env:
    a. if exists: replace, else add to env struct, set exported=1
*/