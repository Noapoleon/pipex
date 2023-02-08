/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/08 14:20:15 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;
	int		i;
	pid_t	pid;
	int		status;

	errno = 0;
	setup_pipex(&pip, ac, av, envp);
	i = 0;
	while (i < pip.cmd_count)
	{
		pip.last_pid = child_process(&pip, i, envp);
		++i;
	}
	close_pipes(&pip);
	i = pip.cmd_count;
	while (i != 0)
	{
		pid = wait(&status);
		if (pid == pip.last_pid)
			pip.ret = status;
		--i;
	}
	pipex_terminate(&pip, WEXITSTATUS(pip.ret));
}

// Forks the process and executes the commands with execve if in child process
pid_t	child_process(t_pipex *pip, int index, char **envp)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		perror("[PIPEX ERROR] child_process > fork");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (index == 0 || index == pip->cmd_count -1)
			open_io_file(pip, index);
		redirect_io(pip, index);
		if (find_cmd(pip, &pip->cmds[index]) == -1)
		{
			ft_dprintf(2, PE_NOCMD, pip->cmds[index].args[0]);
			pipex_terminate(pip, 127);
		}
		if (execve(pip->cmds[index].path, pip->cmds[index].args, envp) == -1)
		{
			ft_dprintf(2, "%s: %s: %s\n", pip->name, pip->cmds[index].path,
				strerror(errno));
			pipex_terminate(pip, EXIT_FAILURE);
		}
	}
	return (pid);
}
