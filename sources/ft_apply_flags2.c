/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flags2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:38:22 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/25 10:38:23 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	добавляет 0 или 0х для 8-иричной и 16-иричной сс в зависимости от флага "#"
*/

char		*ft_num_get_cage_float(char *str, int cage, char type)
{
	char *s;

	if (cage == 1 && type == 'f' && ft_strchr(str, '.') == NULL)
		return (ft_strjoin_free(str, ".", 1, 0));
	if (cage == 1 && type == 'e' && ft_strchr(str, '.') == NULL)
	{
		s = ft_strsub(str, 0, 1);
		if (ft_isdigit(str[0]))
			str[0] = '.';
		else
		{
			str[0] = str[1];
			str[1] = '.';
		}
		return (ft_strjoin_free(s, str, 1, 1));
	}
	return (str);
}
