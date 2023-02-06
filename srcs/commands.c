/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:35:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 11:19:11 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Splits all command strings and stores them in an array of t_cmd
void	make_cmds(t_pipex *pip, char **av)
{
	int	i;

	pip->cmds = ft_calloc(pip->cmd_count, sizeof(t_cmd));
	if (pip->cmds == NULL)
	{
		perror("[PIPEX ERROR] make_cmds > malloc");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	i = 0;
	while (i < pip->cmd_count)
	{
		make_cmd(pip, &pip->cmds[i], av[2 + pip->heredoc + i]);
		++i;
	}
}

// Splits the command string and puts it into the struct
void	make_cmd(t_pipex *pip, t_cmd *cmd, char *cmdstr)
{
	cmd->path = NULL;
	cmd->args = ft_split(cmdstr, ' ');
	if (cmd->args == NULL)
	{
		perror("[PIPEX ERROR] make_cmds -> ft_split");
		pipex_terminate(pip, EXIT_FAILURE);
	}
}
