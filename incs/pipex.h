/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/15 08:54:05 by nlegrand         ###   ########.fr       */
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

# define HEREDOC		"here_doc"
# define DO_PERROR		1
# define DONT_PERROR	0

// USAGE
# define USAGE_N	"Usage: ./pipex <INPUT_FILE> "
# define USAGE_HD	"   or: ./pipex here_doc <LIMITER> "
# define USAGE_CMD	"<cmd1 cmd2> ... <cmdn> <OUTPUT_FILE>\n"

// ERROR MESSAGES
# define PE_NOPATH	"[PIPEX ERROR] no PATH variable in envp.\n"
# define PE_SPLIT	"[PIPEX ERROR] split failed.\n"


typedef struct s_pipex	t_pipex;
typedef struct s_cmd	t_cmd;

struct s_cmd
{
	char			**cmd;
	char			*path;
	struct s_cmd	*next;
	//int			ret; // putting this in advance here in case it's useful, might not need it
};
struct s_pipex
{
	int		fd_if; // haven't checked it that's useful yet
	int		fd_of; // haven't checked it that's useful yet
	char 	**paths;
	t_cmd	*cmds;

	// could probably put main arguments in there for simplicity (e.g.: ac, av, envp)
	// might not be necessary though, we'll see
};


// SETUP
void	setup_pipex(t_pipex *pipex, int ac, char **av, char **encp);
void	init_pipex_vars(t_pipex *pipex);
void	check_inputs(int ac, char **av);
void	get_paths(t_pipex *pipex, char **envp);
void	get_commands(t_pipex *pipex, int ac, char **av);
t_cmd	*get_command(char *cmd_str);

// UTILS
 void	pipex_terminate(t_pipex *pipex); // could use some options too
 void	pipex_exit(t_pipex *pipex, int mode);

// TEST UTILS
void	show_params(int ac, char **av);
void	show_envp(char **envp);
void	show_pipex_state(t_pipex *pipex);
void	do_ls(void);

#endif
