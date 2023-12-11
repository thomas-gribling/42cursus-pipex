/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/11 09:03:36 by tgriblin         ###   ########.fr       */
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

void	proceed(int out)
{
	if (out == 0)
		ft_puterror("Error");
	if (out == -1)
		ft_puterror("No such file or directory");
	if (out == -2)
		ft_puterror("Unable to open files");
	if (out == -3)
		ft_puterror("Pipe error");
}

void	dclose(int *fds1, int *fds2)
{
	close(fds1[0]);
	close(fds1[1]);
	if (fds2)
	{
		close(fds2[0]);
		close(fds2[1]);
	}
}

int	do_pipe(t_pipex pipex, int id)
{
	dup2(pipex.pipes[1 - id], 1 - id);
	close(pipex.pipes[id]);
	dup2(pipex.fd[id], id);
	execve(pipex.cmd[id]->path, pipex.cmd[id]->args, NULL);
	return (1);
}

int	do_pipex(t_pipex pipex, char *f1, char *f2)
{
	if (access(f1, W_OK) < 0)
		return (-1);
	pipex.fd[0] = open(f1, O_RDONLY);
	pipex.fd[1] = open(f2, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (pipex.fd[0] < 0 || pipex.fd[1] < 0)
		return (dclose(pipex.fd, NULL), -2);
	if (pipe(pipex.pipes) < 0)
		return (dclose(pipex.fd, NULL), -3);
	pipex.p[0] = fork();
	if (pipex.p[0] == 0)
		if (!do_pipe(pipex, 0))
			return ((dclose(pipex.fd, pipex.pipes), -3));
	pipex.p[1] = fork();
	if (pipex.p[1] == 0)
		if (!do_pipe(pipex, 1))
			return ((dclose(pipex.fd, pipex.pipes), -3));
	close(pipex.pipes[0]);
	close(pipex.pipes[1]);
	waitpid(pipex.p[0], NULL, 0);
	waitpid(pipex.p[1], NULL, 0);
	return (1);
}
