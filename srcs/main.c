/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:33:10 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/11 09:21:11 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("[%s] ", cmd->path);
	if (cmd->argc)
		while (cmd->args[++i])
			printf("[%s] ", cmd->args[i]);
	printf("- (%d args)\n", cmd->argc - 1);
}*/

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	char	**paths;
	int		i;
	int		error;

	if (ac != 5)
		return (ft_puterror("Invalid number of arguments"), 1);
	paths = get_paths(envp);
	pipex.cmd = malloc((ac - 2) * sizeof(t_cmd *));
	pipex.cmd[ac - 3] = NULL;
	i = -1;
	while (++i < ac - 3)
	{
		pipex.cmd[i] = get_command(paths, av[2 + i]);
		if (!pipex.cmd[i])
		{
			ft_puterror("Command not found");
			return (free_strs(paths), free_cmds(pipex.cmd), 1);
		}
	}
	error = proceed(do_pipex(pipex, av[1], av[ac - 1]));
	free_strs(paths);
	free_cmds(pipex.cmd);
	return (error);
}
