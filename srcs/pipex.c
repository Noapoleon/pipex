/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 16:37:45 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;
	int		i;

	errno = 0;
	//(void)ac;
	//(void)av;
	//(void)envp;
	//char **splitted = ft_split(av[1], ' ');
	//if (splitted == NULL)
	//	ft_printf("pas splitted sa mere\n");
	//else
	//{
	//	ft_printf("splitted addr -> %p\n", splitted);
	//	ft_printf("first thing -> %p\n", splitted[0]);
	//	int i = 0;
	//	while (splitted[i])
	//	{
	//		ft_printf("%d -> %s\n", i, splitted[i]);
	//		++i;
	//	}
	//}
	////char	*truc[2] = {"", NULL};
	//if (execve(splitted[0], splitted, envp) == -1)
	//{
	//	perror("main execve:");
	//}
	//if (splitted != NULL)
	//{
	//	int i = 0;
	//	while (splitted[i])
	//		free(splitted[i++]);
	//	free(splitted);
	//}
	setup_pipex(&pip, ac, av, envp);
	//ft_printf("### PIPEX ###\n");
	//ft_printf("input_file --> %s\n", pip.input_file);
	//ft_printf("output_file --> %s\n", pip.output_file);
	//ft_printf("heredoc -> %d\n", pip.heredoc);
	//ft_printf("cmd_count ---> %d\n", pip.cmd_count);
	//ft_printf("cmds ----> %p\n", pip.cmds);

	//int i = 0;
	//int j;
	//while (i < pip.cmd_count)
	//{
	//	if (find_cmd(&pip, &pip.cmds[i]) == -1)
	//		ft_dprintf(2, PE_NOCMD);
	//	ft_printf("cmd %d:\n", i);
	//	ft_printf("addr -> %p\n", &pip.cmds[i]);
	//	ft_printf("path -> %s\n", pip.cmds[i].path);
	//	j = 0;
	//	while (pip.cmds[i].args[j])
	//	{
	//		ft_printf("args[%d] -> %s\n", j, pip.cmds[i].args[j]);
	//		++j;
	//	}
	//	ft_printf("\n\n");
	//	++i;
	//}
	i = 0;
	while (i < pip.cmd_count)
	{
		child_process(&pip, i, envp);
		++i;
	}
	if (wait(NULL) == -1)
	{
		perror("[PIPEX ERROR] main > wait");
		pipex_terminate(&pip, EXIT_FAILURE);
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
