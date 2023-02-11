/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:35:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/11 17:55:08 by nlegrand         ###   ########.fr       */
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
	if (cmd->args[0] == NULL)
	{
		free(cmd->args);
		cmd->args = malloc(sizeof(char *) * 2);
		if (cmd->args == NULL)
		{
			perror("[PIPEX ERROR] make_cmds -> malloc");
			pipex_terminate(pip, EXIT_FAILURE);
		}
		cmd->args[0] = ft_strdup("");
		if (cmd->args[0] == NULL)
		{
			perror("[PIPEX ERROR] make_cmds -> ft_strdup");
			pipex_terminate(pip, EXIT_FAILURE);
		}
		cmd->args[1] = NULL;
	}
}

// If the command path is local, absolute or non existant this function
// will fill the command struct instead of find_command itself
int	special_cmd_path(t_pipex *pip, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[0][0] == '\0')
		return (-1);
	else if ((cmd->args[0][0] == '/' || cmd->args[0][0] == '.'
			|| pip->paths == NULL) && ++i)
		cmd->path = ft_strdup(cmd->args[0]);
	if (i && cmd->path == NULL)
	{
		perror("[PIPEX ERROR] find_cmd > ft_strdup");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	ft_dprintf(2, "i -> %d\n", i); // remove
	return (i);
}

// Joins the command name with the paths in the PATH variable to find the
// executable
int	find_cmd(t_pipex *pip, t_cmd *cmd)
{
	int		i;
	char	*slashed;

	i = special_cmd_path(pip, cmd);
	if (i > 0)
		return (0);
	else if (i == -1)
		return (-1);
	slashed = ft_strjoin("/", cmd->args[0]);
	if (slashed == NULL)
		return (perror("[PIPEX ERROR] find_cmd > ft_strjoin (1)"),
			pipex_terminate(pip, EXIT_FAILURE), -1);
	i = 0;
	while (pip->paths && pip->paths[i])
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
	return ((cmd->path = NULL), free(slashed), -1);
}
