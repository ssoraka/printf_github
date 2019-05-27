/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_width_accur_specbase_type.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:10:02 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:10:03 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	устанавливает тип для фрагмента строки в листе
*/

void		ft_find_type(t_prlst *list)
{
	if (!((list->temp)[0]))
		list->answer = ft_strdup("");
	else if ((ft_strchr("cCsSpdDioOuUxXfFeEgGbB", (list->temp)[0])))
	{
		list->type = (list->temp)[0];
		list->temp++;
	}
	else
	{
		list->spec = NOTYPE;
		list->type = '%';
		list->answer = ft_chrtoa((list->temp)[0], 0);
		list->temp++;
	}
}

/*
**	устанавливает флаги "+-# 0" для фрагмента строки в листе
*/

void		ft_find_flags(t_prlst *list)
{
	char	*s;

	s = list->temp;
	s++;
	while (*s == '-' || *s == '+' || *s == '#' || *s == ' ' || *s == '0')
	{
		if (*s == '-')
			list->minus = 1;
		if (*s == '+')
			list->plus = 1;
		if (*s == '#')
			list->cage = 1;
		if (*s == ' ')
			list->space = 1;
		if (*s == '0')
			list->zero = 1;
		s++;
	}
	list->temp = s;
}

/*
**	устанавливает ширину для фрагмента строки в листе
*/

void		ft_find_width(t_prlst *list)
{
	char	*str;

	str = list->temp;
	if (!str || !(*str))
		return ;
	if ((list->width = ft_atoi(str)) < 0)
		list->width = 0;
	while (ft_isdigit(*str))
		str++;
	if (*str == '*')
	{
		list->star1 = STAR;
		list->width = 0;
		str++;
	}
	if (*str == '$')
	{
		list->star1 = list->width;
		list->width = 0;
		str++;
	}
	list->temp = str;
}

/*
**	устанавливает точность для фрагмента строки в листе
*/

void		ft_find_accuracy(t_prlst *list)
{
	char	*str;

	str = list->temp;
	if (!str || !(*str) || *str != '.')
		return ;
	str++;
	list->accur = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str == '*')
	{
		list->star2 = STAR;
		list->accur = 0;
		str++;
	}
	if (*str == '$')
	{
		list->star2 = list->accur;
		list->accur = 0;
		str++;
	}
	list->temp = str;
}

/*
**	надо определить спецификатор
*/

void		ft_find_spec(t_prlst *list)
{
	int		i;
	char	specf[8][4];

	i = SPECFCOUNT;
	ft_strcpy(specf[0], "");
	ft_strcpy(specf[1], "h");
	ft_strcpy(specf[2], "l");
	ft_strcpy(specf[3], "hh");
	ft_strcpy(specf[4], "ll");
	ft_strcpy(specf[5], "z");
	ft_strcpy(specf[6], "j");
	ft_strcpy(specf[7], "L");
	if (!(list->temp) || !(*(list->temp)))
		return ;
	while (i > NOTYPE)
	{
		i--;
		if (!(ft_strncmp(specf[i], list->temp, ft_strlen(specf[i]))))
		{
			if (list->spec == NOTYPE)
				list->spec = i;
			list->temp = (list->temp) + ft_strlen(specf[i]);
			break ;
		}
	}
}
