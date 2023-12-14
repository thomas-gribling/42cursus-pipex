/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/14 08:58:53 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	child(int *pipes, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_initferror("pipex: permission denied: %s", av[1]);
	dup2(fd, 0);
	dup2(pipes[1], 1);
	close(pipes[0]);
	paths = get_paths(envp);
	cmd = cmd_get(paths, av[2]);
	tab_free(paths);
	if (!cmd)
	{
		close(fd);
		close(pipes[1]);
		ft_initferror("pipex: command not found: %s", av[2]);
	}
	execve(cmd->path, cmd->args, envp);
}

void	parent(int *pipes, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;

	fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (fd < 0)
		ft_initferror("pipex: permission denied: %s", av[4]);
	dup2(fd, 1);
	dup2(pipes[0], 0);
	close(pipes[1]);
	paths = get_paths(envp);
	cmd = cmd_get(paths, av[3]);
	tab_free(paths);
	if (!cmd)
	{
		close(fd);
		close(pipes[0]);
		ft_initferror("pipex: command not found: %s", av[3]);
	}
	execve(cmd->path, cmd->args, envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	p;
	int		pipes[2];

	if (ac != 5)
		ft_initerror("pipex: arguments error");
	if (access(av[1], R_OK) < 0)
		ft_initferror("pipex: no such file or directory: %s", av[1]);
	if (pipe(pipes) < 0)
		ft_initerror("pipex: pipe error");
	p = fork();
	if (p < 0)
		ft_initerror("pipex: fork error");
	if (p == 0)
		child(pipes, av, envp);
	parent(pipes, av, envp);
	return (0);
}
