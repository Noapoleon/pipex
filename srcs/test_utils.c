/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 04:49:11 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/18 22:02:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_ls(void)
{
	int	ret;
	char	*cmd[] = {"ls", "-la", (char *)0};
	char	*env[] = {"HOME=/usr/home", "LOGNAME=home", (char *)0};
	
	ret = execve("/usr/bin/ls", cmd, env);
	if (ret == -1)
	{
		printf("grosse merde\n");
		perror("do_ls");
	}
}

void	do_all(t_pipex *pipex, char **envp)
{
	t_cmd	*curr;
	int		ret;
	pid_t	parent;
	pid_t	wpid;
	int		status;

	curr = pipex->cmds;
	while (curr != NULL)
	{
		//ret = execve(curr->path, curr->cmd, envp);
		child_pid = fork();
		// check if child_pid is -1 and terminate if so
		if (child_pid == -1)
		{
			perror("fork");
			pipex_exit(pipex);
		}
		else if (!parent)
		{
			ret = execve(curr->path, curr->cmd, envp);
			if (ret == -1)
			{
				perror("execve");
				pipex_exit(pipex);
			}
			pipex_terminate(pipex);
			exit(EXIT_SUCCESS);
		}
		wpid = waitpid(child_pid, &status, 0); // check if options need to be something else than 0
		if (wpid == -1)
		{
			perror("wait");
			pipex_exit(pipex);
		}
		++pipex->cmd_i; // do something different if index is first or last
		curr = curr->next;
	}
}

void	show_params(int ac, char **av)
{
	int	i;

	// input and output files
	// get_files() => does fd checks
	ft_printf("Input file: %s\n", av[1]);
	ft_printf("Output file: %s\n", av[ac - 1]);
	
	// get all n commands
	// get_commands() => might need to do valid function checks
	i = 2;
	while (i < ac - 1)
	{
		ft_printf("cmd%d: \"%s\"\n", i - 1, av[i]);
		++i;
	}
}

void	show_envp(char **envp)
{
	int	i = 0;
	
	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	show_pipex_state(t_pipex *pipex)
{
	ft_printf("### PIPEX STATE ###\n");
	ft_printf("fd_if -> %d\n", pipex->fd_if);
	ft_printf("fd_of -> %d\n\n", pipex->fd_of);
	ft_printf("paths addr -> %p\n", pipex->paths);
	ft_printf("Paths:\n");
	int i = 0;
	while (pipex->paths[i])
	{
		ft_printf("paths[%d] -> %s\n", i, pipex->paths[i]);
		++i;
	}
	t_cmd *curr = pipex->cmds;
	while (curr != NULL)
	{
		ft_printf("commmand ->");
		i = 0;
		while (curr->cmd[i])
			ft_printf(" %s", curr->cmd[i++]);
		ft_printf("\npath -> %s\n", curr->path);
		curr = curr->next;
	}
	ft_printf("###################\n");
}
