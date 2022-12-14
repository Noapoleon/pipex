/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 05:12:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

// open
# include <sys/stat.h>
# include <fcntl.h>
// close, read, write, access, dup, execve, fork, pipe, unlink
# include <unistd.h>
// malloc, free, exit
# include <stdlib.h>
// perror
# include <stdio.h>
// strerror
# include <string.h>
// wait, waitpid
# include <sys/wait.h>

# define HEREDOC	"here_doc"
# define USAGE_N	"Usage: ./pipex <INPUT_FILE> "
# define USAGE_HD	"   or: ./pipex here_doc <LIMITER> "
# define USAGE_CMD	"<cmd1 cmd2> ... <cmdn> <OUTPUT_FILE>\n"

typedef struct s_pipex t_pipex;

struct s_pipex
{
	int	fd_i;
	int	fd_o;
};

// TEST UTILS
void	show_params(int ac, char **av);

#endif