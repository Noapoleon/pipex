/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:53:15 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/22 01:02:21 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	errno = 0; // i think the manual says you can and should do this (or maybe stackoverflow)
	setup_pipex(&pipex, ac, av, envp);
	//show_params(ac, av);
	//show_pipex_state(&pipex);
	//show_envp(envp);
	//do_ls();
	do_all(&pipex, envp);
	pipex_terminate(&pipex, EXIT_SUCCESS);
	return (0);
}
