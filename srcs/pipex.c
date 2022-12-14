/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:53:15 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 19:20:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	errno = 0; // i think the manual says you can and should do this (or maybe stackoverflow)
	check_inputs(ac, av);
	show_params(ac, av);
	//show_envp(envp);
	//do_ls();
	return (0);
}
