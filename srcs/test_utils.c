/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 04:49:11 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/22 01:01:54 by nlegrand         ###   ########.fr       */
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

void	redirect_io(t_pipex *pipex, int	i)
{
	int	error;

	error = 0;
	if (i == 0)
	{
		error += dup2(pipex->fd_if, STDIN_FILENO) == -1;
		error += dup2(pipex->pipes[1], STDOUT_FILENO) == -1;
	}
	else if (i == pipex->cmd_n - 1)
	{
		error += dup2(pipex->pipes[i * 2 - 2], STDIN_FILENO) == -1;
		error += dup2(pipex->fd_of, STDOUT_FILENO) == -1;
	}
	else
	{
		error += dup2(pipex->pipes[i * 2 - 2], STDIN_FILENO) == -1;
		error += dup2(pipex->pipes[i * 2 + 1], STDOUT_FILENO) == -1;
	}
	if (error != 0)
	{
		perror("redirect_io -> dup2");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	close_pipes(pipex);
}
void	child_process(t_pipex *pipex, char **envp)
{
	const t_cmd	*curr = pipex->curr_cmd;
	pid_t	pid;

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

void	do_all(t_pipex *pipex, char **envp)
{
	pipex->curr_cmd = pipex->cmds;
	while (pipex->curr_cmd)
	{
		child_process(pipex, envp);
		++pipex->cmd_i;
		pipex->curr_cmd = pipex->curr_cmd->next;
	}
	if (wait(NULL) == -1) // uuuuuuhm there's 2 children
	{
		perror("do_all -> wait");
		pipex_terminate(pipex, EXIT_FAILURE);
	}
	pipex_terminate(pipex, EXIT_SUCCESS);
}

//void	do_all(t_pipex *pipex, int ac, char **envp)
//{
//	t_cmd	*curr;
//	int		ret;
//	pid_t	child_pid;
//	pid_t	wpid;
//	//int		status;
//	int		fildes[2];
//
//	(void)ac; // REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
//	// PRINTF PROBABLY WONT WORK FOR DEBBUGING AFTER CHANGING THE FDS WITH DUP2
//	if (pipe(fildes) == -1)
//	{
//		perror("pipe");
//		pipex_terminate(pipex, EXIT_FAILURE);
//	}
//	//redirect_io(pipex, fildes[0], fildes[1]); // test
//	close(fildes[1]); // test
//	curr = pipex->cmds;
//	while (curr != NULL)
//	{
//		//ret = execve(curr->path, curr->cmd, envp);
//		child_pid = fork();
//		// check if child_pid is -1 and terminate if so
//		if (child_pid == -1)
//		{
//			perror("fork");
//			pipex_terminate(pipex, EXIT_FAILURE);
//		}
//		else if (child_pid != 0)
//		{
//			close(fildes[0]);
//			close(fildes[1]);
//		}
//		else if (child_pid == 0)
//		{
//			printf("how many time???\n");
//			printf("next?? -> %p\n", curr->next);
//			// OMFG IT WORKING FOR A MOMENT AND I CHANGED SOIMETHING DONT REMEMBER WHAT
//			// but honeslty if i can't replicated it's not worth much...
//			if (pipex->cmd_i == 0)
//			{
//				redirect_io(pipex, pipex->fd_if, fildes[1]); // this function terminates stuff but i have NOT checked at all if some stuff in do_all needs the be freed (like fildes[2] for example, no idea)
////				redirect_io(pipex, pipex->fd_if, 1); // this function terminates stuff but i have NOT checked at all if some stuff in do_all needs the be freed (like fildes[2] for example, no idea)
//				close(pipex->fd_if); // could probably keep them open, if line numbers are not an issue later
//			}
//			else if (pipex->cmd_i == (ac - 4)) // not good index i think?? -4 should be good for normal mode, check for here_doc later
//			{
////				redirect_io(pipex, fildes[0], 1);
//				redirect_io(pipex, fildes[0], pipex->fd_of); // good one (i think)
////				close(pipex->fd_of);
//			}
//			else
//			{
//				redirect_io(pipex, fildes[0], fildes[1]); // THIS SHOULD BE THE GOOD ONE
////				redirect_io(pipex, fildes[1], fildes[0]); // SO WHY DOES THIS ONE KINDA WORK????
////				redirect_io(pipex, fildes[0], 1);
//			}
//			// close correctly here or something (not sure it needs to be here)
//			close(fildes[0]); // can probably close pipe ends here, not sure
//			close(fildes[1]);
//			//close_pipes(fildes);
//			ret = execve(curr->path, curr->cmd, envp);
//			if (ret == -1)
//			{
//				perror("execve");
//				pipex_terminate(pipex, EXIT_FAILURE);
//			}
//			//close(fildes[0]); // probably not here idk, or maybe not this
//			//close(fildes[1]); 
//			pipex_terminate(pipex, EXIT_SUCCESS);
//		}
//		wpid = waitpid(child_pid, NULL, 0); // check if options need to be something else than 0
//		//wpid = waitpid(child, &status, 0); // check if options need to be something else than 0 // don't think i need the status, not sure
//		if (wpid == -1)
//		{
//			perror("waitpid");
//			pipex_terminate(pipex, EXIT_FAILURE);
//		}
//		fprintf(stderr, "cmd_i -> %d\n", pipex->cmd_i);
//		//close(fildes[0]); // doesn't loop but straight up doesn't work anymore, which makes sense
//		//close(fildes[1]);
//		++pipex->cmd_i; // do something different if index is first or last
//		curr = curr->next;
//	}
//	//close(fildes[0]);
//	//close(fildes[1]);
//}

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
