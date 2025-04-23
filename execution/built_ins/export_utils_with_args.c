#include "../../includes/minishell.h"

/*
case 1:
    ** if have: str=str: split on =,
	** maybe add in e_token: TOKEN_VAR
case 2:
	** if have: export str=str: split on =, 
	** maybe add in e_token: TOKEN_VAR
1. if have: str=str: split on =, 
maybe add in e_token: TOKEN_VAR
=============================================
cmd->token_type == TOKEN_EXPORT
cmd->argv == {"export", "VAR=bla", NULL}

int i = 1;
while (cmd->argv[i]) {
    if (!valid_varname(cmd->argv[i])) {
        print_export_error(cmd->argv[i]);
    }
    else if (ft_strchr(cmd->argv[i], '=')) {
        // "VAR=value" → parse key & value
        add_or_replace_env(cmd->argv[i], exported=1);
    } else {
        // "export VAR" → mark as exported
        set_export_flag(cmd->argv[i]);
    }
    i++;
}
valid_varname(char *str)
Check if starts with alpha or _

Remaining: alnum or _
add_or_replace_env(char *arg, int exported)
Split arg on '='

Add new or update value + set exported
set_export_flag(char *key)
If exists in env, set exported = 1

If not: add with value=NULL, exported=1
print_export_error(char *arg)
if (cmd->token_type == TOKEN_WORD && ft_strchr(cmd->argv[0], '=')) {
	add_or_replace_env(cmd->argv[0], exported=0); // Not exported
	return (EXIT_SUCCESS);
}

*/
// int	do_save_var(char **argv, t_env_list *env_struct)
// {
// 	char	*equal_sign;
// 	char	*key;
// 	char	*value;

// 	if (!argv || !argv[0])
// 		return (EXIT_SUCCESS);
// 	equal_sign = ft_strchr(argv[0], '=');
// 	if (!equal_sign)
// 		return (EXIT_SUCCESS); // Not a var assignment
// 	key = ft_substr(argv[0], 0, equal_sign - argv[0]);
// 	value = ft_strdup(equal_sign + 1);
// 	if (!key || !value)
// 		err_malloc(NULL, "minishell: var assign failed");

// 	t_env *existing = find_env(env_struct, key);
// 	if (existing)
// 	{
// 		free(existing->value);
// 		existing->value = value;
// 		existing->exported = 0;
// 	}
// 	else
// 		add_env(env_struct, key, value, 0); // 0 = not exported
// 	free(key);
// 	return (EXIT_SUCCESS);
// }