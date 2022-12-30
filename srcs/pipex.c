/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:53:15 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/30 21:01:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Unimportant function
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	errno = 0;
	setup_pipex(&pipex, ac, av, envp);
	while (pipex.curr_cmd)
	{
		child_process(&pipex, envp);
		++pipex.cmd_i;
		pipex.curr_cmd = pipex.curr_cmd->next;
	}
	if (wait(NULL) == -1)
	{
		perror("do_all -> wait");
		pipex_terminate(&pipex, EXIT_FAILURE);
	}
	pipex_terminate(&pipex, EXIT_SUCCESS);
	return (0);
}

// Executes the command pointed to by curr_cmd
void	child_process(t_pipex *pipex, char **envp)
{
	const t_cmd	*curr = pipex->curr_cmd;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("child_process -> fork");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		redirect_io(pipex, pipex->cmd_i);
		if (execve(curr->path, curr->cmd, envp) == -1)
		{
			perror("child_process -> execve");
			pipex_terminate(pipex, EXIT_FAILURE);
		}
	}
}
