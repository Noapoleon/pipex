/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:00:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/21 04:05:30 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Frees allocated variables in pipex struct and exits program
void	pipex_terminate(t_pipex *pipex, int exit_mode)
{
	int	i; // probably shouldn't close pipes here but not sure

	strarr_clear(&pipex->paths);
	cmdlst_clear(&pipex->cmds);
	close(pipex->fd_if);
	close(pipex->fd_of);
	close_pipes(pipex);
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

void	close_pipes(t_pipex *pipex)
{
	const int	n = pipex->cmd_n * 2;
	int i;

	if (pipex->pipes)
	{
		i = 0;
		while (i < n)
			close(pipex->pipes[i++];
	}
}
