/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:02:03 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/13 16:37:17 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*cmd_build(char *path, char *cmd)
{
	char	*new;

	new = "/";
	new = ft_strjoin(new, cmd, 0);
	new = ft_strjoin(path, new, 2);
	return (new);
}

static int	cmd_find(char **paths, char *cmd)
{
	char	*new;
	char	*curr;
	int		i;

	new = ft_strjoin("/", cmd, 0);
	i = -1;
	while (paths[++i])
	{
		curr = ft_strjoin(paths[i], new, 0);
		if (access(curr, X_OK) >= 0)
			return (free(new), free(curr), i);
		free(curr);
	}
	free(new);
	return (-1);
}

static void	cmd_add_arg(t_cmd *cmd, char *new)
{
	char	**tmp;
	int		i;

	if (!cmd->argc)
	{
		cmd->args = malloc(2 * sizeof(char *));
		cmd->args[0] = ft_strdup(new);
		cmd->args[1] = NULL;
		cmd->argc++;
	}
	else
	{
		tmp = malloc((cmd->argc + 2) * sizeof(char *));
		i = -1;
		while (cmd->args[++i])
			tmp[i] = ft_strdup(cmd->args[i]);
		tmp[i] = ft_strdup(new);
		tmp[i + 1] = NULL;
		tab_free(cmd->args);
		cmd->args = tab_dup(tmp, 0);
		tab_free(tmp);
		cmd->argc++;
	}
}

t_cmd	*cmd_get(char **paths, char *comm)
{
	t_cmd	*cmd;
	char	**tmp;
	int		cmd_path;

	tmp = ft_split(comm, ' ');
	cmd_path = cmd_find(paths, tmp[0]);
	if (cmd_path == -1)
		return (tab_free(tmp), NULL);
	cmd = malloc(sizeof(t_cmd));
	cmd->path = cmd_build(paths[cmd_path], tmp[0]);
	cmd->argc = tab_len(tmp);
	if (cmd->argc > 0)
		cmd->args = tab_dup(tmp, 0);
	else
		cmd_add_arg(cmd, comm);
	tab_free(tmp);
	return (cmd);
}
