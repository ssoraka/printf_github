/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:20:16 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:20:16 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ищем и заменяем цвет
*/

void		ft_replace(char *str, char *repls, int num)
{
	char	color[10];
	size_t	len;

	ft_strcpy(color, "\033[00m");
	if (num < EOC)
	{
		color[2] = '3';
		color[3] = color[3] + num;
	}
	len = ft_strlen(repls);
	ft_memmove(str + 5, str + len, ft_strlen(str + len) + 1);
	ft_memcpy(str, color, 5);
}

/*
**	ищем и заменяем цвет
*/

void		ft_give_color(t_prlst *list)
{
	char	color[9][20];
	int		i;
	char	*str;

	if (list->type != 0 || !(list->answer))
		return ;
	ft_strcpy(color[0], "{black}");
	ft_strcpy(color[1], "{red}");
	ft_strcpy(color[2], "{green}");
	ft_strcpy(color[3], "{yellow}");
	ft_strcpy(color[4], "{blue}");
	ft_strcpy(color[5], "{magenta}");
	ft_strcpy(color[6], "{cyan}");
	ft_strcpy(color[7], "{white}");
	ft_strcpy(color[8], "{eoc}");
	str = list->answer;
	while (str && (str = ft_strchr(str, '{')))
	{
		i = -1;
		while (++i < 9)
			if (!ft_strncmp(str, color[i], ft_strlen(color[i])))
				ft_replace(str, color[i], i);
		str++;
	}
}
