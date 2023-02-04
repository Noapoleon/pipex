/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:55:06 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/04 15:59:18 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Uninportant function :]
int	main(int ac, char **av, char **envp)
{
	//t_pipex	pip;

	(void)ac;
	(void)av;
	(void)envp;
	char **splitted = ft_split(av[1], ' ');
	if (splitted == NULL)
		return (ft_printf("pas splitted sa mere\n"), 0);
	else
	{
		int i = 0;
		while (splitted[i])
		{
			ft_printf("%d -> %s\n", i, splitted[i]);
			free(splitted[i]);
			++i;
		}
		free(splitted);
	}
	//setup_pipex(&pip, ac, av, envp);
	//ft_printf("### PIPEX ###\n");
	//ft_printf("i_file --> %s\n", pip.i_file);
	//ft_printf("o_file --> %s\n", pip.o_file);
	//ft_printf("heredoc -> %d\n", pip.heredoc);
	//ft_printf("n_cmd ---> %d\n", pip.n_cmd);
	//ft_printf("cmds ----> %p\n", pip.cmds);

	//pipex_terminate(&pip, EXIT_SUCCESS);
	return (0);
}
