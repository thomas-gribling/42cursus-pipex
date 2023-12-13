/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/13 16:41:59 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*char	*get_first_word(char *str)
{
	char	**tmp;
	char	*new;

	tmp = ft_split(str, ' ');
	if (!tmp)
		return (NULL);
	new = ft_strdup(tmp[0]);
	tab_free(tmp);
	return (new);
}*/
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
		ft_initerror("Unable to open file");
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
		ft_initerror("Command not found");
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
		ft_initerror("Unable to open file");
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
		ft_initerror("Command not found");
	}
	execve(cmd->path, cmd->args, envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	p[2];
	int		pipes[2];

	if (ac != 5)
		ft_initerror("Args error");
	if (access(av[1], R_OK) < 0)
		ft_initerror("No such file or directory");
	if (pipe(pipes) < 0)
		ft_initerror("Pipe error");
	p[0] = fork();
	if (p[0] < 0)
		ft_initerror("Fork error");
	if (p[0] == 0)
		child(pipes, av, envp);
	p[1] = fork();
	if (p[1] < 0)
		ft_initerror("Fork error");
	if (p[1] == 0)
		parent(pipes, av, envp);
	close(pipes[0]);
	close(pipes[1]);
	return (0);
}
