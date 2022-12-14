/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:46:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 21:34:34 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//
void	setup_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	(void)envp;
	check_inputs(ac, av);
	setup_vars(pipex);
	get_paths(pipex, envp);
	// get_commands(pipex, ac, av);
	// open_files()
	// if (lalala) pipex_terminate()
}

// Prints correct usage if input is bad
void	check_inputs(int ac, char **av)
{
	(void)av;
	// not done, if heredoc then needs to be different
	if (ac < 5 || (ac < 6 && ac >= 2 &&
		ft_memcmp(HEREDOC, av[1], ft_strlen(HEREDOC) + 1) == 0))
	{
		ft_printf(USAGE_N);
		ft_printf(USAGE_CMD);
		ft_printf(USAGE_HD);
		ft_printf(USAGE_CMD);
		exit(EXIT_FAILURE);
	}
}

// Initializes the pipex struct vars to their default values to allow use of
// fdf_terminate() at different stages without causing errors with free
void	setup_vars(t_pipex *pipex)
{
	pipex->fd_if = -1;
	pipex->fd_of = -1;
	pipex->paths = NULL;
}

void	get_paths(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (envp[i] == NULL)
		(ft_dprintf(2, PE_NOPATH), pipex_exit(pipex, DONT_PERROR));
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (pipex->paths == NULL)
		(ft_dprintf(2, PE_SPLIT), pipex_exit(pipex, DO_PERROR));
}
