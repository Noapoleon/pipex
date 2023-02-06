/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:35:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 15:05:33 by nlegrand         ###   ########.fr       */
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

int	special_cmd_path(t_pipex *pip, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[0] == NULL && ++i)
		cmd->path = ft_strdup("");
	else if ((cmd->args[0][0] == '/' || cmd->args[0][0] == '.') && ++i)
		cmd->path = ft_strdup(cmd->args[0]);
	if (i && cmd->path == NULL)
	{
		perror("[PIPEX ERROR] find_cmd > ft_strdup");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	return (i);
}

int	find_cmd(t_pipex *pip, t_cmd *cmd)
{
	int	i;
	char	*slashed;

	if (special_cmd_path(pip, cmd))
		return (0);
	slashed = ft_strjoin("/", cmd->args[0]);
	if (slashed == NULL)
		return (perror("[PIPEX ERROR] find_cmd > ft_strjoin (1)"),
			pipex_terminate(pip, EXIT_FAILURE), -1);
	i = 0;
	while (pip->paths[i])
	{
		cmd->path = ft_strjoin(pip->paths[i++], slashed);
		if (cmd->path == NULL)
			return (free(slashed),
				perror("[PIPEX_ERROR] find_cmd > ft_strjoin (2)"),
				pipex_terminate(pip, EXIT_FAILURE), -1);
		if (access(cmd->path, F_OK) == 0)
			return (free(slashed), 0);
		free(cmd->path);
	}
	return ((cmd->path = NULL), free(slashed), -1); // command not found args[0]
}
