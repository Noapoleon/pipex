/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:21:09 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/30 21:22:34 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Opens pipes all at once, one for every command
void	get_pipes(t_pipex *pipex)
{
	const int	n = pipex->cmd_n * 2;
	int			i;

	pipex->pipes = malloc(sizeof(int) * n);
	if (pipex->pipes == NULL)
	{
		perror("get_pipes -> malloc");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	i = 0;
	while (i < n)
	{
		if (pipe(pipex->pipes + i) == -1)
		{
			perror("get_pipes -> pipe");
			pipex_terminate(pipex, EXIT_FAILURE);
		}
		i += 2;
	}
}

// Reads standard input in a loop until a limiter is found
void	make_heredoc(t_pipex *pipex, int ac, char **av)
{
	const int	len_limiter = ft_strlen(av[2]);
	int			fd;
	char		*line;

	fd = open(HEREPATH, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("make_heredoc -> open");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	while (ft_printf("[pipex] > ") && gnl_w(STDIN_FILENO, &line) != -1)
	{
		if (ft_memcmp(av[2], line, len_limiter) == 0
			&& (line[len_limiter] == '\0' || line[len_limiter] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pipex->fd_if = open(HEREPATH, O_RDONLY);
	pipex->fd_of = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
}
