/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:04:42 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/30 21:30:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Parses commands from main arguments
void	get_commands(t_pipex *pipex, int ac, char **av)
{
	int		i;
	t_cmd	**curr;

	if (ft_memcmp(av[1], HEREARG, ft_strlen(HEREARG) + 1) == 0)
		pipex->heredoc = 1;
	i = 2 + pipex->heredoc;
	curr = &pipex->cmds;
	while (i <= ac - 2)
	{
		*curr = make_cmd(pipex, av[i++]);
		if (*curr == NULL)
			pipex_terminate(pipex, EXIT_FAILURE);
		curr = &(*curr)->next;
	}
	pipex->cmd_n = ac - 3 - pipex->heredoc;
	pipex->curr_cmd = pipex->cmds;
}

t_cmd	*make_cmd(t_pipex *pipex, char *cmdstr)
{
	t_cmd	*tmp;
	int		ret;

	tmp = malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (perror("make_cmd -> malloc"), NULL);
	tmp->cmd = split_cmdstr(cmdstr);
	if (tmp->cmd == NULL)
		return (perror("make_cmd -> ft_split"), free(tmp), NULL);
	ret = find_command(pipex, tmp->cmd[0], &tmp->path);
	if (ret == -1)
		return (strarr_clear(&tmp->cmd), free(tmp), NULL);
	else if (ret == 1)
		return (ft_dprintf(2, E_NOCMD, cmdstr), strarr_clear(&tmp->cmd)
			, free(tmp), NULL);
	tmp->next = NULL;
	return (tmp);
}

int	find_command(t_pipex *pipex, const char *cmd, char **path)
{
	char	*slash;
	int		i;

	if (cmd == NULL)
		slash = ft_strdup("/");
	else
		slash = ft_strjoin("/", cmd);
	if (slash == NULL)
		return (perror("find_command -> ft_strjoin slash"), -1);
	i = 0;
	while (pipex->paths[i])
	{
		*path = ft_strjoin(pipex->paths[i++], slash);
		if (*path == NULL)
			return (perror("find_command -> ft_strjoin path"), free(slash), -1);
		if (access(*path, F_OK) != -1)
			break ;
		free(*path);
		*path = NULL;
	}
	free(slash);
	return (*path == NULL);
}

// Splits the command string into an array using ft_split
// When an empty command is given it will create a special split with an empty
// string and then a NULL and not just NULL like ft_split would
char	**split_cmdstr(char *cmdstr)
{
	char	**tmp;

	tmp = ft_split(cmdstr, ' ');
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != NULL)
		return (tmp);
	else
		strarr_clear(&tmp);
	tmp = malloc(sizeof(char *) * 2);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = ft_strdup("");
	if (tmp[0] == NULL)
		return (NULL);
	tmp[1] = NULL;
	return (tmp);
}
