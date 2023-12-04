/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:02:03 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/04 14:45:29 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_cmd(char **paths, char *cmd)
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

char	*build_path(char *path, char *cmd)
{
	char	*new;

	new = "/";
	new = ft_strjoin(new, cmd, 0);
	new = ft_strjoin(path, new, 2);
	return (new);
}

t_cmd	*get_command(char **paths, char *comm)
{
	t_cmd	*cmd;
	char	**tmp;
	int		cmd_path;

	tmp = ft_split(comm, ' ');
	cmd_path = find_cmd(paths, tmp[0]);
	if (cmd_path == -1)
		return (free(tmp), NULL);
	cmd = malloc(sizeof(t_cmd));
	cmd->path = build_path(paths[cmd_path], tmp[0]);
	cmd->argc = tab_len(tmp);
	if (cmd->argc > 0)
		cmd->args = tab_dup(tmp, 0);
	else
		cmd_add_arg(cmd, comm);
	free_strs(tmp);
	return (cmd);
}

void	cmd_add_arg(t_cmd *cmd, char *new)
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
		free_strs(cmd->args);
		cmd->args = tab_dup(tmp, 0);
		free_strs(tmp);
		cmd->argc++;
	}
}

void	free_cmds(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->path)
			free(cmd[i]->path);
		if (cmd[i]->argc > 0)
			free_strs(cmd[i]->args);
		free(cmd[i]);
	}
	free(cmd);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("[%s] ", cmd->path);
	if (cmd->argc)
		while (cmd->args[++i])
			printf("[%s] ", cmd->args[i]);
	printf("- (%d args)\n", cmd->argc - 1);
}
