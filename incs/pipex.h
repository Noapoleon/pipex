/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 17:47:23 by nlegrand         ###   ########.fr       */
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
// errno
# include <errno.h>
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
	int	fd_if;
	int	fd_of;
};

// UTILS
void	check_inputs(int ac, char **av);




// TEST UTILS
void	show_params(int ac, char **av);
void	show_envp(char **envp);
void	do_ls(void);

#endif
