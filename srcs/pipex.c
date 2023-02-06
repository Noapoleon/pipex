/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 12:43:27 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;

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
	ft_printf("### PIPEX ###\n");
	ft_printf("input_file --> %s\n", pip.input_file);
	ft_printf("output_file --> %s\n", pip.output_file);
	ft_printf("heredoc -> %d\n", pip.heredoc);
	ft_printf("cmd_count ---> %d\n", pip.cmd_count);
	ft_printf("cmds ----> %p\n", pip.cmds);

	pipex_terminate(&pip, EXIT_SUCCESS);
	return (0);
}
