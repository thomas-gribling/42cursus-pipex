/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/08 10:49:21 by tgriblin         ###   ########.fr       */
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

int	do_pipe(t_pipex pipex, int id)
{
	dup2(pipex.pipes[1 - id], 1 - id);
	close(pipex.pipes[id]);
	dup2(pipex.fd[id], id);
	execve(pipex.cmd[id]->path, pipex.cmd[id]->args, NULL);
	return (1);
}

int	check_file(char *f1)
{
	if (access(f1, W_OK) >= 0)
		return (1);
	return (0);
}

int	do_pipex(t_pipex pipex, char *f1, char *f2)
{
	if (!check_file(f1))
		return (0);
	pipex.fd[0] = open(f1, O_RDONLY);
	pipex.fd[1] = open(f2, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (pipex.fd[0] < 0 || pipex.fd[1] < 0)
		return (0);
	if (pipe(pipex.pipes) < 0)
		return (0);
	pipex.p[0] = fork();
	if (pipex.p[0] == 0)
		do_pipe(pipex, 0);
	pipex.p[1] = fork();
	if (pipex.p[1] == 0)
		do_pipe(pipex, 1);
	close(pipex.pipes[0]);
	close(pipex.pipes[1]);
	waitpid(pipex.p[0], NULL, 0);
	waitpid(pipex.p[1], NULL, 0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	t_pipex	pipex;
	int		i;

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
		print_cmd(pipex.cmd[i]); // TEMPORARY
	}
	if (!do_pipex(pipex, av[1], av[ac - 1]))
		ft_puterror("Error");
	free_strs(paths);
	free_cmds(pipex.cmd);
}
