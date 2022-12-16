/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/16 18:44:08 by nlegrand         ###   ########.fr       */
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

// USAGE
# define USAGE_N	"Usage: ./pipex <INPUT_FILE> "
# define USAGE_HD	"   or: ./pipex here_doc <LIMITER> "
# define USAGE_CMD	"<cmd1 cmd2> ... <cmdn> <OUTPUT_FILE>\n"

// ERROR MESSAGES
# define E_EMPTY		"[PIPEX ERROR] Empty pipe argument.\n"
# define E_NOPATH		"[PIPEX ERROR] No PATH variable in envp.\n"
# define E_NOCMD		"[PIPEX ERROR] Command not found: %s\n"


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
t_cmd	*make_cmd(t_pipex *pipex, char *cmd_str);
int		find_command(t_pipex *pipex, const char *cmd, char **path);

// UTILS
void	pipex_terminate(t_pipex *pipex); // could use some options too
void	pipex_exit(t_pipex *pipex);
void	strarr_clear(char ***arr);
void	cmdlst_clear(t_cmd **cmds);


// TEST UTILS
void	show_params(int ac, char **av);
void	show_envp(char **envp);
void	show_pipex_state(t_pipex *pipex);
void	do_ls(void);
void	do_all(t_pipex *pipex, char **envp);

#endif
