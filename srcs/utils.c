/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:00:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/18 22:13:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Frees allocated variables in pipex struct
void	pipex_terminate(t_pipex *pipex, int mode)
{
	strarr_clear(&pipex->paths);
	cmdlst_clear(&pipex->cmds);
	// close fds or something
	if (mode == DO_EXIT)
		exit(EXIT_SUCCESS);
}

// Terminates pipex and exits displaying an error message
void	pipex_exit(t_pipex *pipex)
{
	pipex_terminate(pipex, DONT_EXIT);
//	if (errno != 0)
//		perror("pipex_exit");
	exit(EXIT_FAILURE);
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
