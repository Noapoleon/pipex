/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:35:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/04 15:58:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmd(t_cmd *cmd, char *cmdstr)
{
	cmd->args = ft_split(cmdstr, ' ');
}

void	make_cmds(t_pipex *pip, char **av, char **envp)
{
	int	i;

	(void)av;
	(void)envp;
	pip->cmds = malloc(sizeof(t_cmd) * pip->n_cmd);
	if (pip->cmds == NULL)
	{
		perror("make_cmds -> malloc");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	i = 0;
	while (i < pip->n_cmd)
	{
		ft_printf("cmd #%d\n", i);
		get_cmd(&pip->cmds[i], av[2 + i + pip->heredoc]);
		++i;
	}
}

