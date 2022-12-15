/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:46:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/15 19:09:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//
void	setup_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	(void)envp;
	check_inputs(ac, av);
	init_pipex_vars(pipex);
	get_paths(pipex, envp);
	get_commands(pipex, ac, av);
	// open_files()
	// if (lalala) pipex_terminate()
}

// Prints correct usage if input is bad
void	check_inputs(int ac, char **av)
{
	(void)av;
	// not done, if heredoc then needs to be different
	if (ac < 5 || (ac < 6 && ac >= 2 &&
		ft_strncmp(av[1], HEREDOC, ft_strlen(HEREDOC) + 1) == 0))
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
void	init_pipex_vars(t_pipex *pipex)
{
	pipex->fd_if = -1;
	pipex->fd_of = -1;
	pipex->paths = NULL;
	pipex->cmds = NULL;
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
		ft_dprintf(2, PE_NOPATH);
		pipex_exit(pipex, DONT_PERROR);
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (pipex->paths == NULL)
	{
		ft_dprintf(2, PE_SPLIT);
		pipex_exit(pipex, DO_PERROR);
	}
}

// Parses commands from main arguments
void	get_commands(t_pipex *pipex, int ac, char **av)
{
	int	i;
	t_cmd **curr;

	i = 2 + (ft_strncmp(av[1], HEREDOC, ft_strlen(HEREDOC) + 1) == 0);
	curr = &pipex->cmds;
	while (i <= ac - 2)
	{
		*curr = get_command(av[i++]);
		if (*curr == NULL) // might not even be necessary because of terminate function
			//do_something; terminate or something, needs to be modified to free chained list too now
			pipex_exit(pipex, DO_PERROR);
		curr = &(*curr)->next;
	}
}

t_cmd	*get_command(char *cmd_str)
{
	t_cmd	*tmp;

	// malloc t_cmd node and check bad malloc
	tmp = malloc(sizeof(t_cmd));
	// split command string with spaces (or whitespace???), check fail with NULL
	tmp->cmd = ft_split(cmd_str, ' ');
//	if (tmp->args == NULL)
//		do_something; terminate
	tmp->path = ft_strjoin("/stoopid/dir/", tmp->cmd[0]);
//	if (tmp->path == NULL)
//		terminate or something;
	// check if command exists in one of PATHs using while loop (expand)
	tmp->next = NULL;
	return (tmp);
}

//void	open_files(t_pipex, int ac, char **av)
//{
//
//}
