/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:54:41 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/04 15:49:01 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define USAGE_NORMAL	"Usage: %s <INPUT_FILE> %s\n"
# define USAGE_HEREDOC	"   or: %s here_doc <LIMITER> %s\n"
# define USAGE_CMDS		"<cmd1> <cmd2> ... [cmdn] <OUTPUT_FILE>"

# define HEREDOC "here_doc"

typedef struct s_pipex	t_pipex;
typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	*path;
	char	**args;
};
struct s_pipex
{
	char	*i_file;
	char	*o_file;
	int		heredoc;
	int		n_cmd;
	t_cmd	*cmds;
};

// setup1.c
void	setup_pipex(t_pipex *pip, int ac, char **av, char **envp);
// setup2.c
void	make_cmds(t_pipex *pip, char **av, char **envp);

// utils.c
void	pipex_terminate(t_pipex *pip, int exit_mode);

#endif
