/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:54:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/22 22:40:45 by nlegrand         ###   ########.fr       */
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
};
struct s_pipex
{
	int		fd_if;
	int		fd_of;
	char 	**paths;
	t_cmd	*cmds;
	int		cmd_n;
	int		cmd_i;
	t_cmd	*curr_cmd;
	int		*pipes;
};

// PIPEX
void	child_process(t_pipex *pipex, char **envp);

// SETUP
void	setup_pipex(t_pipex *pipex, int ac, char **av, char **envp);
void	init_pipex_vars(t_pipex *pipex);
void	check_inputs(int ac, char **av);
void	get_paths(t_pipex *pipex, char **envp);
void	get_files(t_pipex *pipex, int ac, char **av);
// SETUP 2
void	get_commands(t_pipex *pipex, int ac, char **av);
t_cmd	*make_cmd(t_pipex *pipex, char *cmd_str);
int		find_command(t_pipex *pipex, const char *cmd, char **path);
void	get_pipes(t_pipex *pipex);

// UTILS
void	pipex_terminate(t_pipex *pipex, int mode); // could use some options too
void	strarr_clear(char ***arr);
void	cmdlst_clear(t_cmd **cmds);
void	close_pipes(t_pipex *pipex);
void	redirect_io(t_pipex *pipex, int i);


// TEST UTILS // remoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooove later
//void	show_params(int ac, char **av);
//void	show_envp(char **envp);
//void	show_pipex_state(t_pipex *pipex);
//void	do_ls(void);
//void	do_all(t_pipex *pipex, char **envp);

#endif
