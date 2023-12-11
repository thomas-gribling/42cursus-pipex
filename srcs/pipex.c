/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:14:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/11 17:15:33 by tgriblin         ###   ########.fr       */
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

void	child(t_pipex pipex, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;

	paths = get_paths(envp);
	cmd = get_command(paths, av[2]);
	if (!cmd)
		ft_initerror("Command not found");
	free_strs(paths);
	fd = open(av[1], O_RDONLY);
	dup2(fd, 0);
	dup2(pipex.pipes[1], 1);
	close(pipex.pipes[0]);
	execve(cmd->path, cmd->args, envp);
}

void	parent(t_pipex pipex, char **av, char **envp)
{
	t_cmd	*cmd;
	char	**paths;
	int		fd;

	paths = get_paths(envp);
	cmd = get_command(paths, av[3]);
	if (!cmd)
		ft_initerror("Command not found");
	free_strs(paths);
	fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	dup2(fd, 1);
	dup2(pipex.pipes[0], 0);
	close(pipex.pipes[1]);
	execve(cmd->path, cmd->args, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	__pid_t	p;

	if (ac != 5)
		ft_initerror("Args error");
	if (access(av[1], W_OK) < 0)
		ft_initerror("No such file or directory");
	if (pipe(pipex.pipes) < 0)
		ft_initerror("Args error");
	p = fork();
	if (p < 0)
		ft_initerror("Pipe error");
	if (p == 0)
		child(pipex, av, envp);
	parent(pipex, av, envp);
}
