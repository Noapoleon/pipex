/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/12 00:39:43 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;
	pid_t	pid;
	int		status;

	errno = 0;
	setup_pipex(&pip, ac, av, envp);
	while (pip.cmd_index < pip.cmd_count)
	{
		pip.last_pid = child_process(&pip, &pip.cmds[pip.cmd_index], envp);
		++pip.cmd_index;
	}
	close_pipes(&pip);
	while (pip.cmd_index--)
	{
		pid = wait(&status);
		if (pid == pip.last_pid)
			pip.ret = status;
	}
	pipex_terminate(&pip, WEXITSTATUS(pip.ret));
}

// Forks the process and executes the commands with execve if in child process
pid_t	child_process(t_pipex *pip, t_cmd *cmd, char **envp)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		perror("[PIPEX ERROR] child_process > fork");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (pip->cmd_index == 0 || pip->cmd_index == pip->cmd_count -1)
			open_io_file(pip, pip->cmd_index);
		redirect_io(pip, pip->cmd_index);
		if (find_cmd(pip, cmd) == -1)
		{
			ft_dprintf(2, PE_NOCMD, pip->name, cmd->args[0]);
			pipex_terminate(pip, 127);
		}
		if (execve(cmd->path, cmd->args, envp) == -1)
		{
			ft_dprintf(2, "%s: %s: %s\n", pip->name, cmd->path,
				strerror(errno));
			pipex_terminate(pip, EXIT_FAILURE);
		}
	}
	return (pid);
}
