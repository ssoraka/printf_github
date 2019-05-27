/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_width_accur_specbase_type2.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:10:02 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:10:03 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	приведение необычных типов к базовым
*/

void		ft_change_type(t_prlst *list)
{
	if (list->type == 'X' || list->type == 'E' || list->type == 'G' ||
		list->type == 'F')
	{
		list->type = list->type - 'A' + 'a';
		list->captls = 1;
	}
	if (list->type == 'D' || list->type == 'O' || list->type == 'U')
	{
		list->type = list->type - 'A' + 'a';
		list->spec = L;
	}
	if (list->type == 'S' || list->type == 'C')
	{
		list->type = list->type - 'A' + 'a';
		list->spec = L;
	}
	if (list->type == 'p')
		list->cage = 1;
}

/*
**	приведение неправильных спецификаторов к базовым
*/

void		ft_change_spec(t_prlst *list)
{
	if (ft_strchr("douixb", list->type) && list->spec == LF)
		list->spec = NOTYPE;
	if (ft_strchr("cs", list->type) && list->spec == LL)
		list->spec = L;
	if (ft_strchr("cs", list->type) && list->spec == J)
		list->spec = L;
	if (ft_strchr("cs", list->type) && list->spec == Z)
		list->spec = L;
	if (ft_strchr("cs", list->type) && list->spec != L)
		list->spec = NOTYPE;
	if (ft_strchr("fegB", list->type) && list->spec == LL)
		list->spec = L;
	else if (ft_strchr("fegB", list->type) && list->spec != LF &&
		list->spec != L)
		list->spec = NOTYPE;
}
