#include "pipex.h"

void	show_params(int ac, char **av)
{
	int	i;

	// show usage in case of bad use
	if (ac < 5)
		(ft_printf(USAGE), exit(EXIT_FAILURE));

	// input and output files
	ft_printf("Input file: %s\n", av[1]);
	ft_printf("Output file: %s\n", av[ac - 1]);
	
	// get all n commands
	i = 2;
	while (i < ac - 1)
	{
		ft_printf("cmd%d: \"%s\"\n", i - 1, av[i]);
		++i;
	}
}
