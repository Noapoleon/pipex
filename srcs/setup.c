/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:46:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/30 10:29:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Prepares all pipex variables and opens files for proper pipex processing
void	setup_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	check_inputs(ac, av);
	init_pipex_vars(pipex);
	get_paths(pipex, envp);
	get_commands(pipex, ac, av);
	get_files(pipex, ac, av);
	get_pipes(pipex);
}

// Prints correct usage if input is bad
void	check_inputs(int ac, char **av)
{
	int	i;

	if (ac < 5 || (ac < 6 && ac >= 2
			&& ft_strncmp(av[1], HEREARG, ft_strlen(HEREARG) + 1) == 0))
	{
		ft_printf(USAGE_N);
		ft_printf(USAGE_CMD);
		ft_printf(USAGE_HD);
		ft_printf(USAGE_CMD);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (av[i])
	{
		if (av[i][0] == '\0')
		{
			ft_dprintf(2, E_EMPTY);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}

// Initializes the pipex struct vars to their default values to allow use of
// pipex_terminate() at different stages without causing errors with free
void	init_pipex_vars(t_pipex *pipex)
{
	pipex->fd_if = -1;
	pipex->fd_of = -1;
	pipex->paths = NULL;
	pipex->cmds = NULL;
	pipex->cmd_n = 0;
	pipex->cmd_i = 0;
	pipex->curr_cmd = NULL;
	pipex->pipes = NULL;
	pipex->heredoc = 0;
}

// Uses main's argument envp to get PATH variable
// Will be used to find functions
void	get_paths(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (envp[i] == NULL)
	{
		ft_dprintf(2, E_NOPATH);
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (pipex->paths == NULL)
	{
		perror("get_paths -> ft_split");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
}

// Open input and output files
void	get_files(t_pipex *pipex, int ac, char **av)
{
	if (pipex->heredoc)
		make_heredoc(pipex, ac, av);
	else
	{
		pipex->fd_if = open(av[1], O_RDONLY);
		pipex->fd_of = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	if (pipex->fd_if == -1 || pipex->fd_of == -1)
	{
		perror("get_files -> open");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
}
