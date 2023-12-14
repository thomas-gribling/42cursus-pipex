/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:27:24 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/14 08:33:56 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char		*path;
	int			argc;
	char		**args;
}				t_cmd;

// Core functions
t_cmd	*cmd_get(char **paths, char *comm);
// Utils functions
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2, int do_free);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strdup(const char *s);
void	ft_initerror(char *str);
void	ft_initferror(char *str, char *s);
char	**tab_dup(char **tab, int start);
int		tab_len(char **tab);
void	tab_free(char **strs);

#endif