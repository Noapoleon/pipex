/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:00:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 21:20:46 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_terminate(t_pipex *pipex)
{
	int	i;
	ft_printf("terminating... or something\n");
	i = 0;
	while (pipex->paths && pipex->paths[i])
		free(pipex->paths[i++]);
	free(pipex->paths);
	// close fds or something
}

void	pipex_exit(t_pipex *pipex, int mode)
{
	pipex_terminate(pipex);
	ft_printf("something went bad lol idk\n"); // change that later
	if (mode == DO_PERROR)
		perror("somewhere idfk"); // change that later
	exit(EXIT_FAILURE);
}
