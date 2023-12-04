/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/04 11:27:23 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_file(char *f1)
{
	if (access(f1, W_OK) >= 0)
		return (1);
	return (0);
}

int	pipex(t_cmd **cmd, char *f1, char *f2)
{
	__pid_t	p;

	if (!check_file(f1))
		return (0);
	//if f2 doesn't exist
		// create it
	p = fork();
	if (p < 0)
		return (0);
	//if (p == 0)
		// child
	//else
		// parent
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	t_cmd	**cmd;
	int		i;

	if (ac > 4)
	{
		cmd = malloc((ac - 2) * sizeof(t_cmd *));
		cmd[ac - 3] = NULL;
		paths = get_paths(envp);
		i = -1;
		while (++i < ac - 3)
		{
			cmd[i] = get_command(paths, av[2 + i]);
			if (!cmd[i])
			{
				ft_puterror("Error!");
				return (free_strs(paths), free_cmds(cmd), 1);
			}
			cmd_add_arg(cmd[i], av[ac - 1]);
			print_cmd(cmd[i]);
		}
		//if (!pipex(cmd, av[1], av[ac - 1]))
		//	ft_puterror("Error!");
		free_strs(paths);
		free_cmds(cmd);
	}
	else
		ft_puterror("Error!");
}
