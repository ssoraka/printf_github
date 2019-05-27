/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:31:38 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:31:39 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	укорачиваем строку по точности
*/

char		*ft_cut_str(char *str, int accur, int type, int spec)
{
	int len;

	if (ft_strchr("di", type) && !ft_strcmp(str, "0") && accur == 0)
		str[0] = '\0';
	if (type != 's')
		return (str);
	len = ft_strlen(str);
	if (spec == L)
	{
		if (len > 0 && accur >= 0)
			str[ft_next_utf8(str, accur)] = '\0';
	}
	else
	{
		if (len > accur && accur >= 0)
			str[accur] = '\0';
	}
	return (str);
}

/*
**	выводим все строки ответов
*/

int			ft_put_answer(t_prlst *list)
{
	int		count;

	count = 0;
	while (list != NULL)
	{
		if (list->count_symb == 1 && list->minus == 1)
		{
			write(1, "", 1);
			count++;
			list->count_symb--;
		}
		list->count_symb = list->count_symb + ft_strlen(list->answer);
		write(1, list->answer, list->count_symb);
		free(list->answer);
		list->answer = NULL;
		count = count + list->count_symb;
		list = list->next;
	}
	return (count);
}

/*
**	для вывода только целых букв
*/

int			ft_next_utf8(const char *str, int accuracy)
{
	int		i;
	int		n;
	int		utf8;

	i = 0;
	n = 0;
	while (str[i] && i <= accuracy)
	{
		if ((unsigned char)str[i] >= 240)
			utf8 = 4;
		else if ((unsigned char)str[i] >= 224)
			utf8 = 3;
		else if ((unsigned char)str[i] >= 192)
			utf8 = 2;
		else
			utf8 = 1;
		i = i + utf8;
		n++;
	}
	if (i > accuracy)
		i = i - utf8;
	return (i);
}
