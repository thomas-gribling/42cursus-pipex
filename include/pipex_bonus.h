/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:44:49 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/18 10:09:53 by tgriblin         ###   ########.fr       */
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
	pid_t		p;
}				t_pipex;

void	do_pipex(int ac, char **av, char **envp);
char	**get_paths(char **envp);

#endif