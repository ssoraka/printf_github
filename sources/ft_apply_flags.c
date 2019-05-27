/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:22:01 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:22:02 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	добавляет пробел в начало в зависимости от флага " "
*/

char		*ft_num_get_space(char *str, int space)
{
	int len;

	len = ft_strlen(str);
	if (space == 0)
		return (str);
	if (!str)
		str = ft_strdup(" ");
	else if (str[0] != '-' && str[0] != '+')
		str = ft_strjoin_free(" ", str, 0, 1);
	return (str);
}

/*
**	добавляет кучу нулей слева от числа в зависимости от флага "+"
*/

char		*ft_num_get_znak(char *str, int plus)
{
	if (!str || plus == 0 || str[0] == '-')
		return (str);
	return (ft_strjoin_free("+", str, 0, 1));
}

/*
**	добавляет 0 или 0х для 8-иричной и 16-иричной сс в зависимости от флага "#"
*/

char		*ft_num_get_cage(char *str, int cage, char type, int accur)
{
	if (type != 'p' && (cage == 0 || !str || !(ft_strcmp(str, "0"))))
		return (str);
	if (type == 'p' || type == 'x')
	{
		if (str[0] == '0' && str[1] == '0' && str[2] && accur < 0)
			str[1] = 'x';
		else if (str[0] == '0' && str[1] && accur < 0)
		{
			str[0] = 'x';
			return (ft_strjoin_free("0", str, 0, 1));
		}
		else
			return (ft_strjoin_free("0x", str, 0, 1));
	}
	if (type == 'o')
		if (str[0] != '0')
			return (ft_strjoin_free("0", str, 0, 1));
	return (str);
}

/*
**	добавляет кучу нулей слева от числа в зависимости от флага "0"
*/

char		*ft_num_stretch_zero(char *str, int width, int zero, int accur)
{
	int		len;
	char	*zeros;
	char	znak;

	znak = '0';
	if (!ft_strcmp(str, "0") && accur == 1 && width == 0)
		str[0] = '\0';
	len = ft_strlen(str);
	if (str[0] &&
		(str[0] == '-' || str[0] == '+' || str[0] == ' ') && accur == 1)
		len--;
	if (width <= len || zero == 0)
		return (str);
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
	{
		znak = str[0];
		str[0] = '0';
	}
	width = width - len;
	zeros = ft_strnew(width);
	ft_memset((void *)zeros, '0', width);
	zeros[0] = znak;
	return (ft_strjoin_free(zeros, str, 1, 1));
}

/*
**	добавляет кучу пробелов слева или справа от числа в зависимости от флага "-"
*/

char		*ft_num_stretch_spaces(char *str, int width, int minus)
{
	int		len;
	char	*spaces;

	len = ft_strlen(str);
	width = width - len;
	if (width <= 0)
		return (str);
	spaces = ft_strnew(width);
	ft_memset((void *)spaces, ' ', width);
	if (minus == 1)
		return (ft_strjoin_free(str, spaces, 1, 1));
	else
		return (ft_strjoin_free(spaces, str, 1, 1));
}
