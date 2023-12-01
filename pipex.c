/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/01 11:06:57 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

char **get_paths(char **envp)
{
	char **strs;
	char *tmp;
	int i;

	strs = NULL;
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			strs = ft_split(envp[i], ':');
	tmp = malloc(ft_strlen(strs[0]) - 4);
	i = 4;
	while (strs[0][++i])
		tmp[i - 5] = strs[0][i];
	tmp[i - 5] = '\0';
	free(strs[0]);
	strs[0] = malloc(ft_strlen(tmp) + 1);
	i = -1;
	while (tmp[++i])
		strs[0][i] = tmp[i];
	strs[0][i] = '\0';
	free(tmp);
	return (strs);
}

int find_cmd(char **paths, char *cmd)
{
	char *new;
	char *curr;
	int i;

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

char *build_path(char *path, char *cmd)
{
	char *new;

	new = "/";
	new = ft_strjoin(new, cmd, 0);
	new = ft_strjoin(path, new, 2);
	return (new);
}

t_cmd *get_command(char **paths, char *comm)
{
	t_cmd *cmd;
	char **tmp;
	int cmd_path;

	tmp = ft_split(comm, ' ');
	cmd_path = find_cmd(paths, tmp[0]);
	if (cmd_path == -1)
		return (free(tmp), NULL);
	cmd = malloc(sizeof(t_cmd));
	cmd->exe = build_path(paths[cmd_path], tmp[0]);
	cmd->args = tab_dup(tmp, 1);
	free_strs(tmp);
	return (cmd);
}

void free_cmds(t_cmd **cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->exe)
			free(cmd[i]->exe);
		if (cmd[i]->args)
			free_strs(cmd[i]->args);
		free(cmd[i]);
	}
	free(cmd);
}

int check_file(char *f1)
{
	if (access(f1, W_OK) >= 0)
		return (1);
	return (0);
}

int pipex(t_cmd **cmd, char *f1, char *f2)
{
	__pid_t	p;
	
	if (!check_file(f1))
		return (0);
	//if (access(f2, W_OK) < 0)
		// create it
	p = fork();
	if (p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	//if (p == 0)
		// child
	return (1);
}

int main(int ac, char **av, char **envp)
{
	char	**paths;
	t_cmd	**cmd;
	int 	i;

	if (ac > 4)
	{
		cmd = malloc((ac - 3) * sizeof(t_cmd *));
		paths = get_paths(envp);
		i = -1;
		while (++i < ac - 3)
		{
			cmd[i] = get_command(paths, av[2 + i]);
			if (!cmd[i])
			{
				perror("Error!");
				return (free_strs(paths), free_cmds(cmd), 1);
			}
			//printf("[%s] [%s] [%s]\n", cmd[i]->exe, cmd[i]->args[0], cmd[i]->args[1]);
		}
		if (!pipex(cmd, av[1], av[ac - 1]))
			perror(strerror(ERR_FILE));
		free_strs(paths);
		//free_cmds(cmd);
	}
	else
		perror("error");
}
