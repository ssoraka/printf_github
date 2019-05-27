/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:03:18 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:03:19 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	преобразует число long в строку по основанию base
*/

char		*ft_ltoa_base(long num, int base)
{
	char			temp[50];
	int				znak;
	char			chr;
	unsigned long	n;
	size_t			i;

	i = 0;
	znak = 1;
	n = num;
	if (base > 16 || base < 2)
		return (0);
	if (base == 10 && num < 0)
		znak = -1;
	ft_bzero(temp, 50);
	while (n != 0 || i == 0)
	{
		chr = n % base;
		temp[i] = chr < 10 ? chr + '0' : chr + 'a' - 10;
		n = n / base;
		i++;
	}
	if (znak < 0)
		temp[i] = '-';
	ft_strrevers(temp);
	return (ft_strdup(temp));
}
