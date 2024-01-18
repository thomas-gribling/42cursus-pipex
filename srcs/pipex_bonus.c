/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:43:45 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/18 14:38:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"

void	first(t_pipex *px, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_initferror("pipex: permission denied: %s", av[1]);
	dup2(fd, 0);
	dup2(px->pipe[0][1], 1);
	close(px->pipe[0][0]);
	paths = get_paths(envp);
	cmd = cmd_get(paths, av[2]);
	tab_free(paths);
	if (!cmd)
	{
		close(fd);
		close(px->pipe[0][1]);
		ft_initferror("pipex: command not found: %s", av[2]);
	}
	execve(cmd->path, cmd->args, envp);
}

void	middle(t_pipex *px, char **av, char **envp, int curr)
{
	t_cmd	*cmd;
	char	**paths;
	int		i;

	dup2(px->pipe[curr - 1][0], 0);
	dup2(px->pipe[curr][1], 1);
	i = -1;
	while (++i < curr - 1)
	{
		close(px->pipe[i][0]);
		close(px->pipe[i][1]);
	}
	close(px->pipe[curr - 1][1]);
	close(px->pipe[curr][0]);
	paths = get_paths(envp);
	cmd = cmd_get(paths, av[2 + curr]);
	tab_free(paths);
	if (!cmd)
	{
		close(px->pipe[curr - 1][0]);
		close(px->pipe[curr][1]);
		ft_initferror("pipex: command not found: %s", av[2 + curr]);
	}
	execve(cmd->path, cmd->args, envp);
}

void	last(t_pipex *px, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;
	int		i;

	fd = open(av[px->cmd_amt + 2], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (fd < 0)
		ft_initferror("pipex: permission denied: %s", av[px->cmd_amt + 2]);
	dup2(fd, 1);
	dup2(px->pipe[px->cmd_amt - 2][0], 0);
	i = -1;
	while (++i < px->cmd_amt - 2)
	{
		close(px->pipe[i][0]);
		close(px->pipe[i][1]);
	}
	close(px->pipe[px->cmd_amt - 2][1]);
	paths = get_paths(envp);
	cmd = cmd_get(paths, av[px->cmd_amt + 1]);
	tab_free(paths);
	if (!cmd)
	{
		close(fd);
		close(px->pipe[px->cmd_amt - 2][0]);
		ft_initferror("pipex: command not found: %s", av[px->cmd_amt + 1]);
	}
	execve(cmd->path, cmd->args, envp);
}

void	call_pipex(t_pipex *px, char **av, char **envp, int curr)
{
	if (curr == 0)
		first(px, av, envp);
	else
		middle(px, av, envp, curr);
}

void	do_pipex(int ac, char **av, char **envp)
{
	t_pipex	*px;
	int		i;

	if (access(av[1], R_OK) < 0)
		ft_initferror("pipex: no such file or directory: %s", av[1]);
	px = malloc(sizeof(t_pipex));
	px->cmd_amt = ac - 3;
	px->pipe = malloc((px->cmd_amt - 1) * sizeof(int *));
	px->here_d = 0;
	i = -1;
	while (++i < px->cmd_amt - 1)
	{
		px->pipe[i] = malloc(2 * sizeof(int));
		if (pipe(px->pipe[i]))
			ft_initerror("pipex: pipe error");
		px->p = fork();
		if (px->p < 0)
			ft_initerror("pipex: fork error");
		if (px->p == 0)
			call_pipex(px, av, envp, i);
	}
	last(px, av, envp);
}
