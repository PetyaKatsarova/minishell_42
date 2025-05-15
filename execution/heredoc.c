/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:20:14 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/15 10:56:36 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	write_heredoc_to_tmp(char *str)
{
	char	*name;
	char	*tmp;
	int		fd;
	static int	count = 0;

	tmp = ft_itoa(count++);
	if (!tmp)
		return (-1);
	name = ft_strjoin("hd_", tmp);
	free(tmp);
	if (!name)
		return (-1);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0 || write(fd, str, ft_strlen(str)) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (free(name), -1);
	}
	close(fd);
	fd = open(name, O_RDONLY);
	unlink(name);
	return (free(name), fd);
}

int	apply_heredoc(t_node *redir)
{
	int	fd;

	if (!redir || !redir->heredoc_str)
		return (EXIT_FAILURE);
	fd = write_heredoc_to_tmp(redir->heredoc_str);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
