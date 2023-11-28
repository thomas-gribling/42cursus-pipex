/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:27:24 by tgriblin          #+#    #+#             */
/*   Updated: 2023/11/28 09:42:33 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*get_first_word(char *str);

#endif