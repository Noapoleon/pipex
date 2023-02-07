/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/07 16:16:56 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;
	int		i;

	errno = 0;
	setup_pipex(&pip, ac, av, envp);
	i = 0;
	while (i < pip.cmd_count)
	{
		child_process(&pip, i, envp);
		++i;
	}
	i = pip.cmd_count;
	while (i != 0)
	{
		wait(NULL);
		--i;
		ft_printf("%d children left\n", i);
	//if (wait(NULL) == -1)
	//{
	//	perror("[PIPEX ERROR] main > wait");
	//	pipex_terminate(&pip, EXIT_FAILURE);
	//}
	}
	pipex_terminate(&pip, EXIT_SUCCESS);
	return (0);
}

void	child_process(t_pipex *pip, int index, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("[PIPEX ERROR] child_process > fork");
		pipex_terminate(pip, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if ((index == 0 || index == pip->cmd_count -1)
			&& open_io_file(pip, index) == -1)
			pipex_terminate(pip, EXIT_FAILURE);
		redirect_io(pip, index);
		if (find_cmd(pip, &pip->cmds[index]) == -1)
			ft_dprintf(2, PE_NOCMD);
		if (execve(pip->cmds[index].path, pip->cmds[index].args, envp) == -1)
		{
			perror("[PIPEX ERROR] child_process > execve");
			pipex_terminate(pip, EXIT_FAILURE);
		}
	}
}
