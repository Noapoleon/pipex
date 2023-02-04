/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:25:49 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/04 15:49:07 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Checks that pipex was provided with the good amount of input for either
// normal or here_doc mode
static void	check_input(int ac, char **av)
{
	if (ac < 5
		|| (ac < 6 && ft_strncmp(HEREDOC, av[1], ft_strlen(HEREDOC) + 1) == 0))
	{
		ft_printf(USAGE_NORMAL, av[0], USAGE_CMDS);
		ft_printf(USAGE_HEREDOC, av[0], USAGE_CMDS);
		exit(EXIT_FAILURE);
	}
}

// Sets pipex attributes that don't need any memory allocations
static void	init_pipex_vars(t_pipex *pip, int ac, char **av)
{
	pip->heredoc = ft_strncmp(HEREDOC, av[1], ft_strlen(HEREDOC) + 1) == 0;
	pip->n_cmd = ac - 3 - pip->heredoc;
	if (!pip->heredoc)
		pip->i_file = av[1];
	else
		pip->i_file = NULL;
	pip->o_file = av[ac - 1];
	pip->cmds = NULL;
}

// Sets up variables in pipex struct, safely allocates everything
void	setup_pipex(t_pipex *pip, int ac, char **av, char **envp)
{
	(void)envp; // remove later
	(void)ac; // remove later
	(void)av; // remove later
	check_input(ac, av);
	init_pipex_vars(pip, ac, av);
	make_cmds(pip, av, envp);
}
