/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:45:47 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/11 15:17:19 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**tab_dup(char **tab, int start)
{
	char	**out;
	int		i;

	i = 0;
	while (tab[start + i])
		i++;
	out = malloc((i + 1) * sizeof(char *));
	i = start - 1;
	while (tab[++i])
		out[i - start] = ft_strdup(tab[i]);
	out[i - start] = NULL;
	return (out);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	ft_puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	write(2, "\n", 1);
}

void	ft_initerror(char *str)
{
	ft_puterror(str);
	exit(1);
}
