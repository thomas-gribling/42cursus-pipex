/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:44:49 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/22 09:17:03 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"
# include <stdio.h>

typedef struct s_pipex
{
	int			cmd_amt;
	int			**pipe;
	int			pipe_here_doc[2];
	pid_t		p;
}				t_pipex;

void	do_pipex(int ac, char **av, char **envp);
void	do_heredoc(int ac, char **av, char **envp);
void	read_heredoc(t_pipex *px, char **av);

void	close_all_pipes(t_pipex *px, int curr);
char	**get_paths(char **envp);

int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);

#endif