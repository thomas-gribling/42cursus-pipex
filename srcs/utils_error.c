/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:47:00 by tgriblin          #+#    #+#             */
/*   Updated: 2023/12/14 08:48:08 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_initerror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	write(2, "\n", 1);
	exit(1);
}

static void	ft_puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
}

void	ft_initferror(char *str, char *s)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '%' && str[i + 1] == 's')
		{
			ft_puterror(s);
			i += 1;
		}
		else
			write(2, &str[i], 1);
	}
	write(2, "\n", 1);
	exit(1);
}
