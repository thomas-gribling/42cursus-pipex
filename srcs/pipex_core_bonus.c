/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_core_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:01:08 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/22 09:17:51 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/gnl.h"

void	close_all_pipes(t_pipex *px, int curr)
{
	int	i;

	i = -1;
	while (++i < curr)
	{
		close(px->pipe[i][0]);
		close(px->pipe[i][1]);
	}
}

void	read_heredoc(t_pipex *px, char **av)
{
	char	*line;
	char	*limiter;
	char	*buffer;

	limiter = ft_strjoin(av[2], "\n", 0);
	write(1, "pipex heredoc> ", 15);
	line = get_next_line(0);
	buffer = ft_strdup("");
	while (ft_strcmp(line, limiter))
	{
		buffer = ft_strjoin(buffer, line, 3);
		write(1, "pipex heredoc> ", 15);
		line = get_next_line(0);
	}
	ft_putstr_fd(buffer, px->pipe_here_doc[1]);
	free(buffer);
	free(limiter);
}
