/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:04:42 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/22 00:56:22 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			pipex_terminate(pipex, EXIT_FAILURE);
		curr = &(*curr)->next;
	}
	pipex->cmd_n = ac - 3; // change for heredoc
}

t_cmd	*make_cmd(t_pipex *pipex, char *cmd_str)
{
	t_cmd	*tmp;
	int		ret;

	tmp = malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (perror("make_cmd -> malloc"), NULL);
	tmp->cmd = ft_split(cmd_str, ' ');
	if (tmp->cmd == NULL)
		return (perror("make_cmd -> ft_split"), free(tmp), NULL);
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
		return (perror("find_command -> ft_strjoin"), -1);
	i = 0;
	while (pipex->paths[i])
	{
		*path = ft_strjoin(pipex->paths[i++], slashed);
		if (*path == NULL)
			return (perror("find_command -> ft_strjoin"), free(slashed), -1);
		if (access(*path, F_OK) != -1)
			break ;
		free(*path);
		*path = NULL;
	}
	if (*path == NULL)
		return (1);
	return (0);
}

// Opens pipes all at once, one for every command
void	get_pipes(t_pipex *pipex)
{
	const int	n = pipex->cmd_n * 2;
	int	i;

	pipex->pipes = malloc(sizeof(int) * n);
	if (pipex->pipes == NULL)
	{
		perror("get_pipes -> malloc");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	i = 0;
	while (i < n)
	{
		if (pipe(pipex->pipes + i) == -1)
		{
			perror("get_pipes -> pipe");
			pipex_terminate(pipex, EXIT_FAILURE);
		}
		i += 2;
	}
}
