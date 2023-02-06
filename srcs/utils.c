/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:36:36 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 15:42:44 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_terminate(t_pipex *pip, int exit_mode)
{
	free_cmds(pip);
	close_pipes(pip);
	free(pip->pipes);
	strarr_clear(pip->paths);
	exit(exit_mode);
}

void	free_cmds(t_pipex *pip)
{
	int	i;

	if (pip->cmds == NULL)
		return ;
	i = 0;
	while (i < pip->cmd_count)
	{
		free(pip->cmds[i].path);
		strarr_clear(pip->cmds[i].args);
		++i;
	}
	free(pip->cmds);
}

// Frees an array of strings
void	strarr_clear(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	close_pipes(t_pipex *pip)
{
	int i = 0;

	if (pip->pipes)
		while (i < pip->cmd_count * 2)
			close(pip->pipes[i++]);
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
