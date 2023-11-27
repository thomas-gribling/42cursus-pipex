/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/11/27 16:33:06 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "pipex.h"

char	**get_paths(char **envp)
{
	char	**strs;
	char	*tmp;
	int		i;

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

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

int	find_cmd(char **paths, char *cmd)
{
	char	*new;
	char	*curr;
	int		i;

	new = "/";
	new = ft_strjoin(new, cmd);
	i = -1;
	while (paths[++i])
	{
		curr = ft_strjoin(paths[i], new);
		if (access(curr, X_OK) >= 0)
			return (free(new), free(curr), i);
		free(curr);
	}
	free(new);
	return (-1);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	//int		*cmd_path;
	int		i;

	if (ac > 4)
	{
		//cmd_path = malloc((ac - 3) * sizeof(int));
		paths = get_paths(envp);
		//i = -1;
		//while (++i < ac - 3)
		//	cmd_path[i] = find_cmd(paths, av[2 + i]);
		i = -1;
		printf("file1: %s\nfile2: %s\n", av[1], av[ac - 1]);
		while (++i < ac - 3)
			printf("cmd%d: %s\n", i + 1, av[2 + i]);
		free_strs(paths);
		//free(cmd_path);
	}
	else
		write(2, "Error\n", 6);
}
