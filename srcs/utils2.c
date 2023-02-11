/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:14:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/11 23:12:25 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Opens the input or output file depending on the index given
void	open_io_file(t_pipex *pip, int index)
{
	if (index == 0 && pip->heredoc)
		make_heredoc(pip);
	else if (index == 0)
		pip->fd_if = open(pip->in_file, O_RDONLY);
	else if (index == pip->cmd_count -1 && pip->heredoc)
		pip->fd_of = open(pip->out_file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (index == pip->cmd_count - 1)
		pip->fd_of = open(pip->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (pip->fd_if == -1 || pip->fd_of == -1)
	{
		if (pip->fd_if == -1)
			ft_dprintf(2, "%s: %s: %s\n", pip->name, pip->in_file,
				strerror(errno));
		else
			ft_dprintf(2, "%s: %s: %s\n", pip->name, pip->out_file,
				strerror(errno));
		pipex_terminate(pip, EXIT_FAILURE);
	}
}

int	heredoc_set_joined(char **joined, char *line)
{
	char	*tmp;

	if (*joined == NULL)
		*joined = ft_strdup(line);
	else
	{
		tmp = *joined;
		*joined = ft_strjoin(*joined, line);
		free(tmp);
	}
	free(line);
	if (*joined == NULL)
		return (perror("[PIPEX ERROR] heredoc_set_joined"), -1);
	return (0);
}

// Reads standard input in a loop and writes to the specified fd
// Doesn't stop when Ctrl+D is pressed
int	heredoc_loop(t_pipex *pip, int fd, char **line, char **joined)
{
	while (1)
	{
		if (*joined == NULL)
			write(1, "> ", 2);
		*line = get_next_line(0);
		if (*line == NULL && *joined != NULL)
			continue ;
		else if (*line == NULL && *joined == NULL)
			return (ft_printf("\n%s: warning: here-document delimited by \
end-of-file (wanted `%s')\n", pip->name, pip->limiter), 0);
		if (heredoc_set_joined(joined, *line) == -1)
			return (-1);
		if (ft_strncmp(*joined, pip->limiter, ft_strlen(pip->limiter)) == 0)
			if ((*joined)[ft_strlen(pip->limiter)] == '\n')
				return (free(*joined), 0);
		if ((*joined)[ft_strlen(*joined) - 1] == '\n')
		{
			write(fd, *joined, ft_strlen(*joined));
			free(*joined);
			*joined = NULL;
		}
	}
	return (0);
}

// Creates a temporary file and reads standard input in a loop until a limiter
// is found
void	make_heredoc(t_pipex *pip)
{
	int		fd;
	char	*line;
	char	*joined;

	fd = open(HEREPATH, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("[PIPEX ERROR] make_heredoc > open");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	joined = NULL;
	if (heredoc_loop(pip, fd, &line, &joined) == -1)
	{
		close(fd);
		perror("[PIPEX ERROR] make_heredoc > heredoc_loop");
		exit(EXIT_FAILURE);
	}
	close(fd);
	pip->fd_if = open(HEREPATH, O_RDONLY);
}
