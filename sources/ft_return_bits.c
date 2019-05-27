/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_values_to_str3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:23:43 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:23:43 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	помещает в ответ строку битовое представление числа
*/

void		ft_return_btoa_to_answer(t_prlst *list)
{
	int		size;
	char	*ptr;
	float	f;
	double	d;

	f = (float)(list->fvalue);
	d = (double)(list->fvalue);
	if (list->type != 'b' && list->type != 'B')
		return ;
	if (list->type == 'B')
		size = ft_size_from_spec(list->spec, 1);
	else
		size = ft_size_from_spec(list->spec, 0);
	if (list->type == 'b')
		ptr = (char *)(&(list->dvalue));
	else if (list->type == 'B' && list->spec == LF)
		ptr = (char *)(&(list->fvalue));
	else if (list->type == 'B' && list->spec == L)
		ptr = (char *)(&d);
	else
		ptr = (char *)(&f);
	list->answer = ft_bytes_to_bits(ptr, size, "  ");
	list->answer[ft_strlen(list->answer) - 1] = '\0';
}

/*
**	возвращает количество байт в зависимости от спецификатора
*/

int			ft_size_from_spec(int spec, int ldfloat)
{
	int		size;

	if (spec == LF && ldfloat == 1)
		size = 16;
	else if (spec == H && ldfloat == 0)
		size = 2;
	else if (spec == HH && ldfloat == 0)
		size = 1;
	else if (spec == NOTYPE)
		size = 4;
	else
		size = 8;
	return (size);
}
