/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:27:24 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/01 09:58:19 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ERR_FILE 2
# define ERR_ARG 22

typedef struct s_cmd
{
	char		*exe;
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

#endif