/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 03:42:57 by nlegrand         ###   ########.fr       */
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

# define USAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"

// TEST UTILS
void	show_params(int ac, char **av);

#endif
