/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:00:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/30 21:19:35 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Frees allocated variables in pipex struct and exits program
void	pipex_terminate(t_pipex *pipex, int exit_mode)
{
	strarr_clear(&pipex->paths);
	cmdlst_clear(&pipex->cmds);
	close(pipex->fd_if);
	close(pipex->fd_of);
	close_pipes(pipex);
	free(pipex->pipes);
	unlink(HEREPATH);
	exit(exit_mode);
}

// Frees an array of strings and sets it to NULL
void	strarr_clear(char ***arr)
{
	int	i;

	if (*arr)
	{
		i = 0;
		while ((*arr)[i])
			free((*arr)[i++]);
		free(*arr);
		*arr = NULL;
	}
}

// Frees a list of t_cmd commands and sets it to NULL
void	cmdlst_clear(t_cmd **cmds)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (*cmds)
	{
		curr = *cmds;
		while (curr != NULL)
		{
			tmp = curr;
			strarr_clear(&curr->cmd);
			free(curr->path);
			curr = curr->next;
			free(tmp);
		}
		*cmds = NULL;
	}
}

// Closes all pipe file descriptors previously opened in pipex_setup()
// Note that some file descriptors might already be closed when this function
// is called as the child processes sometimes closes the pipes to avoid loop
// in execve
void	close_pipes(t_pipex *pipex)
{
	const int	n = pipex->cmd_n * 2;
	int			i;

	if (pipex->pipes)
	{
		i = 0;
		while (i < n)
			close(pipex->pipes[i++]);
	}
}

// Uses dup2 to redirect the standard io to the correct files descriptors
// depending on the index of the command being executed
void	redirect_io(t_pipex *pipex, int i)
{
	int	error;

	error = 0;
	if (i == 0)
		error += dup2(pipex->fd_if, STDIN_FILENO) == -1;
	else
		error += dup2(pipex->pipes[i * 2 - 2], STDIN_FILENO) == -1;
	if (i == pipex->cmd_n - 1)
		error += dup2(pipex->fd_of, STDOUT_FILENO) == -1;
	else
		error += dup2(pipex->pipes[i * 2 + 1], STDOUT_FILENO) == -1;
	if (error != 0)
	{
		perror("redirect_io -> dup2");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	close_pipes(pipex);
}
