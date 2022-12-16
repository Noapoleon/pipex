/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:46:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/16 06:07:37 by nlegrand         ###   ########.fr       */
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
	int	i;

	if (ac < 5 || (ac < 6 && ac >= 2 &&
		ft_strncmp(av[1], HEREDOC, ft_strlen(HEREDOC) + 1) == 0))
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
		ft_dprintf(2, E_NOPATH);
		pipex_exit(pipex);
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (pipex->paths == NULL)
	{
		perror("get_paths");
		pipex_exit(pipex);
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
		*curr = make_cmd(pipex, av[i++]);
		if (*curr == NULL)
			pipex_exit(pipex);
		curr = &(*curr)->next;
	}
}

t_cmd	*make_cmd(t_pipex *pipex, char *cmd_str)
{
	t_cmd	*tmp;
	int		ret;

	tmp = malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (perror("make_cmd"), NULL);
	tmp->cmd = ft_split(cmd_str, ' ');
	if (tmp->cmd == NULL)
		return (perror("make_cmd"), free(tmp), NULL);
	ret = find_command(pipex, tmp->cmd[0], &tmp->path);
	if (ret == -1)
		return (strarr_clear(&tmp->cmd), free(tmp), NULL);
	else if (ret == 1)
		return (ft_dprintf(2, E_NOCMD, cmd_str), strarr_clear(&tmp->cmd)
			, free(tmp), NULL);
	tmp->next = NULL;
	return (tmp);
}

int	find_command(t_pipex *pipex, const char *cmd, char **path)
{
	char	*slashed;
	int			i;

	slashed = ft_strjoin("/", cmd);
	if (slashed == NULL)
		return (perror("find_command"), -1);
	i = 0;
	while (pipex->paths[i])
	{
		*path = ft_strjoin(pipex->paths[i++], slashed);
		if (*path == NULL)
			return (perror("find_command"), free(slashed), -1);
		if (access(*path, F_OK) != -1)
			break ;
		free(*path);
		*path = NULL;
	}
	if (*path == NULL)
		return (1);
	return (0);
}

//void	open_files(t_pipex, int ac, char **av)
//{
//
//}
