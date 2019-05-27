/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:17:12 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:17:13 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	самая главная управляющая функция ft_printf
*/

int			ft_printf(char *format, ...)
{
	va_list	ap;
	t_prlst	*list;
	t_prlst	*args;
	size_t	len;

	list = ft_str_to_list(format);
	va_start(ap, format);
	args = ft_return_list_of_args(list);
	ft_get_stars(ap, list, args);
	va_end(ap);
	ft_listiter(list, &ft_create_answers);
	len = ft_put_answer(list);
	ft_listdel(&list);
	ft_listdel(&args);
	return (len);
}

/*
**	парсим строку на флаги, спецификаторы и тиы в каждом листе списка
*/

void		ft_change_lists(t_prlst *list)
{
	char *str;

	str = ft_strchr(list->temp, '%');
	if (!str)
	{
		list->answer = ft_strdup(list->temp);
		list->temp = NULL;
	}
	else if (str > list->temp)
	{
		list->answer = ft_strsub(list->temp, 0, str - list->temp);
		list->temp = str;
		list->type = 't';
	}
	else if (str == list->temp)
	{
		ft_find_flags(list);
		ft_find_width(list);
		ft_find_accuracy(list);
		ft_find_spec(list);
		ft_find_type(list);
		ft_change_type(list);
		ft_change_spec(list);
		ft_get_number_of_arg(list);
	}
}

/*
**	формируем строки для печати у всех элементов списка
*/

void		ft_create_answers(t_prlst *list)
{
	ft_return_btoa_to_answer(list);
	ft_return_ltoa_to_answer(list);
	ft_return_chrtoa_to_answer(list);
	ft_return_oxtoa_to_answer(list);
	ft_return_ldtoa_to_answer(list);
	ft_change_flags(list);
	ft_apply_flags_to_answer(list);
	ft_give_color(list);
}

/*
**	меняем флаги в соответствии с их иерархией
*/

void		ft_change_flags(t_prlst *list)
{
	if (list->width < 0)
	{
		list->width = -(list->width);
		list->minus = 1;
	}
	list->width = list->width - list->count_symb;
	if (ft_strchr("cspoxubB", list->type) != NULL)
		list->plus = 0;
	if (ft_strchr("bBn", list->type) != NULL)
		list->zero = 0;
	if (ft_strchr("cspoxubB%", list->type) != NULL)
		list->space = 0;
	if (ft_strchr("csdiubB%n", list->type) != NULL)
		list->cage = 0;
	if (list->type == 'x' && ft_strcmp(list->answer, "0") == 0)
		list->cage = 0;
	if (ft_strchr("diuox", list->type) != NULL && list->accur >= 0)
		list->zero = 0;
	if (list->plus == 1)
		list->space = 0;
	if (list->minus == 1)
		list->zero = 0;
}

/*
**	применяем флаги к строке ответа
*/

void		ft_apply_flags_to_answer(t_prlst *list)
{
	char *str;

	str = list->answer;
	str = ft_cut_str(str, list->accur, list->type, list->spec);
	str = ft_num_get_znak(str, list->plus);
	str = ft_num_get_space(str, list->space);
	str = ft_num_stretch_zero(str, list->width, list->zero, 0);
	if (ft_strchr("diuoxp", list->type) != NULL)
		str = ft_num_stretch_zero(str, list->accur, 1, 1);
	str = ft_num_get_cage(str, list->cage, list->type, list->accur);
	str = ft_num_get_cage_float(str, list->cage, list->type);
	str = ft_num_stretch_spaces(str, list->width, list->minus);
	if (list->captls == 1)
		str = ft_strupcase(str);
	list->answer = str;
}
