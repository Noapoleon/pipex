/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 04:49:11 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 05:05:47 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_params(int ac, char **av)
{
	int	i;

	// show usage in case of bad use
	// check_input()
	if (ac < 5)
	{
		ft_printf(USAGE_N);
		ft_printf(USAGE_CMD);
		ft_printf(USAGE_HD);
		ft_printf(USAGE_CMD);
		exit(EXIT_FAILURE);
	}

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
