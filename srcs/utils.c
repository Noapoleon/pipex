/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:36:36 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 12:31:28 by nlegrand         ###   ########.fr       */
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
