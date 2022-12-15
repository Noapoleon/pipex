/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:00:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/15 19:10:47 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Frees allocated variables in pipex struct
void	pipex_terminate(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths && pipex->paths[i])
		free(pipex->paths[i++]);
	free(pipex->paths);
	// close fds or something
}

// Terminates pipex and exits displaying an error message
void	pipex_exit(t_pipex *pipex, int mode)
{
	pipex_terminate(pipex);
	if (mode == DO_PERROR)
		perror("somewhere idfk"); // change that later
	exit(EXIT_FAILURE);
}

