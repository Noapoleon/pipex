/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:25:49 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 16:03:08 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Sets up variables in pipex struct, safely allocates everything
void	setup_pipex(t_pipex *pip, int ac, char **av, char **envp)
{
	check_input(ac, av);
	init_pipex_vars(pip, ac, av);
	get_paths(pip, envp);
	make_cmds(pip, av);
	open_pipes(pip);
}

// Checks that pipex was provided with the good amount of input for either
// normal or here_doc mode
void	check_input(int ac, char **av)
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
// Attributes that do need allocation are set to NULL
void	init_pipex_vars(t_pipex *pip, int ac, char **av)
{
	pip->heredoc = ft_strncmp(HEREDOC, av[1], ft_strlen(HEREDOC) + 1) == 0;
	pip->cmd_count = ac - 3 - pip->heredoc;
	if (!pip->heredoc)
		pip->input_file = av[1];
	else
		pip->input_file = NULL;
	pip->output_file = av[ac - 1];
	pip->fd_if = -2;
	pip->fd_of = -2;
	pip->paths = NULL;
	pip->cmds = NULL;
	pip->pipes = NULL;
}

// Finds the PATH variable in envp and splits it into an array of strings
void	get_paths(t_pipex *pip, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], PATH, ft_strlen(PATH)) == 0)
			break ;
		++i;
	}
	if (envp[i] == NULL)
	{
		ft_dprintf(2, PE_NOPATH);
		pipex_terminate(pip, EXIT_FAILURE);
	}
	pip->paths = ft_split(envp[i] + ft_strlen(PATH), ':');
	if (pip->paths == NULL)
	{
		perror("[PIPEX ERROR] get_paths > ft_split");
		pipex_terminate(pip, EXIT_FAILURE);
	}
}

void	open_pipes(t_pipex *pip)
{
	int	i;

	pip->pipes = malloc(sizeof(int) * (pip->cmd_count * 2));
	if (pip->pipes == NULL)
	{
		perror("[PIPEX ERROR] get_pipes > malloc");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	i = 0;
	while (i < pip->cmd_count * 2)
	{
		if (pipe(pip->pipes + i) == -1)
		{
			perror("[PIPEX_ERROR] get_pipes > pipe");
			pipex_terminate(pip, EXIT_FAILURE);
		}
		i += 2;
	}
}
