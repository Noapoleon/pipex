/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:14:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/07 20:22:19 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Opens the input or output file depending on the index given
int	open_io_file(t_pipex *pip, int index)
{
	if (index == 0)
	{
		if (pip->heredoc)
			make_heredoc(pip);
		else
			pip->fd_if = open(pip->input_file, O_RDONLY);
		if (pip->fd_if == -1)
		{
			perror("[PIPEX ERROR] open_io_file > open input");
			pipex_terminate(pip, EXIT_FAILURE);
		}
	}
	else
	{
		pip->fd_of = open(pip->output_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (pip->fd_of == -1)
		{
			perror("[PIPEX ERROR] open_io_file > open output");
			pipex_terminate(pip, EXIT_FAILURE);
		}
	}
	return (0);
}

// Creates a temporary file and reads standard input in a loop until a limiter
// is found
void	make_heredoc(t_pipex *pip)
{
	const int	len_limiter = ft_strlen(pip->limiter);
	int			fd;
	char		*line;

	fd = open(HEREPATH, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("[PIPEX ERROR] make_heredoc > open");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	while (ft_printf("[pipex] > ") && gnl_w(STDIN_FILENO, &line) != -1)
	{
		if (ft_memcmp(pip->limiter, line, len_limiter) == 0
			&& (line[len_limiter] == '\0' || line[len_limiter] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pip->fd_if = open(HEREPATH, O_RDONLY);
}
