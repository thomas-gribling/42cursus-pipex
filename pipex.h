/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:27:24 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/05 09:01:47 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_FILE 2
# define ERR_ARG 22

typedef struct s_cmd
{
	char		*path;
	int			argc;
	char		**args;
}				t_cmd;

char	*ft_strjoin(char *s1, char *s2, int do_free);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strdup(const char *s);
char	**tab_dup(char **tab, int start);
int		tab_len(char **tab);
char	*get_first_word(char *str);
void	free_strs(char **strs);
void	ft_puterror(char *str);

t_cmd	*get_command(char **paths, char *comm);
void	cmd_add_arg(t_cmd *cmd, char *new);
void	free_cmds(t_cmd **cmd);
void	print_cmd(t_cmd *cmd);

#endif