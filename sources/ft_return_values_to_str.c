/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_values_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:23:43 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:23:43 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	заменяем все условные номера аргументов на их содержимое
**	с учетом типов данных
*/

void		ft_get_stars(va_list ap, t_prlst *list, t_prlst *args)
{
	while (list != NULL)
	{
		if (list->star1 > 0)
			list->width = (int)ft_return_arg(ap, list->star1, args);
		if (list->width > 2147483640 || list->width < -2147483640)
			list->width = 0;
		list->star1 = 0;
		if (list->star2 > 0)
			list->accur = (int)ft_return_arg(ap, list->star2, args);
		if (list->accur > 2147483640 || list->accur < 0)
			list->accur = -1;
		list->star2 = 0;
		list->dvalue = 0;
		list->fvalue = 0;
		if (ft_strchr("cspdiouxb", list->type))
			list->dvalue = ft_return_arg(ap, list->num, args);
		if (ft_strchr("fegB", list->type))
			list->fvalue = ft_return_argf(ap, list->num, args);
		list = list->next;
	}
	va_end(ap);
}

/*
**	возвращаем long аргумент под соответствующим номером
*/

long		ft_return_arg(va_list ap, int arg_numb, t_prlst *l_args)
{
	int			i;
	long		dnum;
	va_list		arg;

	va_copy(arg, ap);
	i = 1;
	dnum = 0;
	while (i <= arg_numb)
	{
		if (ft_strchr("cspdiouxb*", l_args->type))
			dnum = (long)va_arg(arg, long);
		l_args = l_args->next;
		i++;
	}
	va_end(arg);
	return (dnum);
}

/*
**	возвращаем long double аргумент под соответствующим номером
*/

long double	ft_return_argf(va_list ap, int arg_numb, t_prlst *l_args)
{
	int			i;
	long double	fnum;
	va_list		arg;

	va_copy(arg, ap);
	i = 1;
	fnum = 0;
	while (i <= arg_numb)
	{
		if (ft_strchr("fegB", l_args->type))
		{
			if (l_args->spec == LF)
				fnum = (long double)va_arg(arg, long double);
			else
				fnum = (long double)va_arg(arg, double);
		}
		l_args = l_args->next;
		i++;
	}
	va_end(arg);
	return (fnum);
}

/*
**	помещает в ответ строку из числа в 8-иричной или 16-ричной форме
*/

void		ft_return_oxtoa_to_answer(t_prlst *list)
{
	int		base;

	base = 8;
	if (list->answer != NULL || ft_strchr("ox", list->type) == NULL)
		return ;
	if (list->type == 'x')
		base = 16;
	if (list->spec == NOTYPE)
		list->answer = ft_ltoa_base((unsigned int)list->dvalue, base);
	else if (list->spec == H)
		list->answer = ft_ltoa_base((unsigned short)list->dvalue, base);
	else if (list->spec == HH)
		list->answer = ft_ltoa_base((unsigned char)list->dvalue, base);
	else
		list->answer = ft_ltoa_base(list->dvalue, base);
}

/*
**	помещает в ответ строку из числа
*/

void		ft_return_ltoa_to_answer(t_prlst *list)
{
	if (list->answer != NULL || ft_strchr("diu", list->type) == NULL)
		return ;
	if (list->type == 'u')
	{
		if (list->spec == NOTYPE)
			list->answer = ft_ultoa((unsigned int)(list->dvalue));
		else if (list->spec == H)
			list->answer = ft_ultoa((unsigned short)(list->dvalue));
		else if (list->spec == HH)
			list->answer = ft_ultoa((unsigned char)(list->dvalue));
		else
			list->answer = ft_ultoa((list->dvalue));
	}
	else
	{
		if (list->spec == NOTYPE)
			list->answer = ft_ltoa((int)(list->dvalue));
		else if (list->spec == H)
			list->answer = ft_ltoa((short)(list->dvalue));
		else if (list->spec == HH)
			list->answer = ft_ltoa((char)(list->dvalue));
		else
			list->answer = ft_ltoa((list->dvalue));
	}
}
