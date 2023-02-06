/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:54:41 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/06 11:19:12 by nlegrand         ###   ########.fr       */
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

# define PE_NOPATH	"[PIPEX ERROR] No path variable found.\n"

# define HEREDOC	"here_doc"
# define PATH		"PATH="

typedef struct s_pipex	t_pipex;
typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	*path;
	char	**args;
};
struct s_pipex
{
	char	*input_file;
	char	*output_file;
	char	**paths;
	int		heredoc;
	int		cmd_count;
	t_cmd	*cmds;
	int		*pipes;
};

// setup1.c
void	setup_pipex(t_pipex *pip, int ac, char **av, char **envp);
void	check_input(int ac, char **av);
void	init_pipex_vars(t_pipex *pip, int ac, char **av);
void	get_paths(t_pipex *pip, char **envp);
void	open_pipes(t_pipex *pip);

// commands.c
void	make_cmds(t_pipex *pip, char **av);
void	make_cmd(t_pipex *pip, t_cmd *cmd, char *cmdstr);
//void	find_cmd(

// utils.c
void	pipex_terminate(t_pipex *pip, int exit_mode);
void	free_cmds(t_pipex *pip);
void	strarr_clear(char **arr);
void	close_pipes(t_pipex *pip);

#endif
