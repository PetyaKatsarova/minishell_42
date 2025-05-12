/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_heredoc.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/06 13:56:14 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/06 13:56:16 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	parse_line(	char **cpy_new,
						char **cpy_input,
						t_parsing_data *data,
						bool exp)
{
	while (**cpy_input != '\0')
	{
		if (exp == true && **cpy_input == '$')
		{
			expand(cpy_new, cpy_input, data);
		}
		else
		{
			copy_char(cpy_new, cpy_input, data);
		}
	}
	**cpy_new = '\n';
}

static void	heredoc_loop(char *delim, t_parsing_data *data, bool exp)
{
	char	*input;
	char	*cpy_new;
	char	*cpy_input;
	int		cpy_stdin;

	cpy_stdin = dup(STDIN_FILENO);
	if (cpy_stdin == -1)
	{
		perror("dup");
		exit_failure_parser(data);
	}
	cpy_new = data->new;
	if (setup_sigint_heredoc() == -1)
	{
		exit_failure_parser(data);
	}
	input = readline("> ");
	while (input != NULL && my_strcmp(input, delim) != 0)
	{
		while (*cpy_new != '\0')
		{
			cpy_new++;
		}
		cpy_input = input;
		parse_line(&cpy_new, &cpy_input, data, exp);
		free(input);
		input = readline("> ");
	}
	if (g_signum == SIGINT)
	{
		errno = 0;
		if (dup2(cpy_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(cpy_stdin);
			exit_failure_parser(data);
		}
	}
	if (g_signum != SIGINT && input == NULL)
	{
		write(1, "warning: heredoc delimited by EOF\n", 34);
	}
	if (setup_sigint_prompt() == -1)
	{
		exit_failure_parser(data);
	}
	close(cpy_stdin);
	free(input);
}

static void	extract_delim(char *delim, bool *exp)
{
	if (*delim == '\'' || *delim == '\"')
	{
		*exp = false;
		delim++;
		while (*delim != '\0')
		{
			*(delim - 1) = *delim;
			delim++;
		}
		delim--;
		*delim = '\0';
		delim--;
		*delim = '\0';
	}
	else
	{
		*exp = true;
	}
}

char	*parse_heredoc(char *delim, t_parsing_data *data)
{
	bool	exp;

	data->new = allocate_str(data);
	extract_delim(delim, &exp);
	heredoc_loop(delim, data, exp);
	return (data->new);
}
