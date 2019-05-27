/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_arithmetic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:40:04 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:40:05 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	делим строку чаров на цифру
*/

void		ft_division_str_num(char *str, int n, int accuracy)
{
	int		overfl;
	int		i;
	long	*l;

	overfl = 0;
	i = 0;
	if (n >= '0')
		n = n - '0';
	l = (long *)(str);
	while (str[i] == '0')
		i++;
	while (i < accuracy)
	{
		if (str[i] >= '0')
			str[i] = str[i] - '0';
		str[i] = str[i] + overfl;
		overfl = (str[i] % n) * 10;
		str[i] = str[i] / n + '0';
		i++;
	}
}

/*
**	прибавляем строку чаров к другой строке
*/

void		ft_summ_str_str(char *answer, char *str, int shift)
{
	int		overfl;
	int		i;
	int		len;

	overfl = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len || overfl > 0)
	{
		if (answer[i + shift] == '.')
			shift++;
		if (answer[i + shift] >= '0')
			answer[i + shift] = answer[i + shift] - '0';
		if (str[i] >= '0')
			str[i] = str[i] - '0';
		answer[i + shift] = str[i] + answer[i + shift] + overfl;
		overfl = answer[i + shift] / 10;
		answer[i + shift] = answer[i + shift] % 10 + '0';
		if (str[i] < '0')
			str[i] = str[i] + '0';
		i++;
	}
}

/*
**	заносит в строку ответ целую часть числа в обратном направлении
*/

void		ft_natural_part(t_plist *p)
{
	int		i;
	char	**str;

	i = 0;
	if (!(str = ft_str_arr_new(2, p->pow_10)))
		return ;
	str[0][0] = (p->maxpow_2 < 0) ? '0' : '1';
	str[1][0] = '0';
	while (i <= p->maxpow_2)
	{
		if (i > 0)
			ft_summ_str_str(str[0], str[0], 0);
		if (i == p->nminpow_2)
		{
			if ((p->ld_bits & p->mask_nat) != 0)
				ft_summ_str_str(str[1], str[0], 0);
			p->nminpow_2++;
			p->mask_nat = p->mask_nat << 1;
		}
		i++;
	}
	p->answer = ft_strdup(str[1]);
	ft_strrevers(p->answer);
	ft_str_arr_free(str);
}

/*
**	заносит в строку ответ дробную часть числа в прямом порядке
*/

void		ft_decimal_part(t_plist *p, int accuracy)
{
	int		i;
	char	**str;

	str = ft_str_arr_new(2, accuracy);
	ft_memset(str[0], '0', accuracy);
	str[0][0] = (p->minpow_2 > -1) ? '0' : '5';
	ft_memset(str[1], '0', accuracy);
	i = -1;
	while (i >= p->minpow_2)
	{
		if (i == p->dmaxpow_2)
		{
			if ((p->ld_bits & p->mask_dec) != 0)
			{
				ft_summ_str_str(str[1], ft_strrevers(str[0]), 0);
				ft_strrevers(str[0]);
			}
			p->dmaxpow_2--;
			p->mask_dec = p->mask_dec >> 1;
		}
		ft_division_str_num(str[0], 2, accuracy);
		i--;
	}
	p->answer = ft_strjoin_free((p->answer), ft_strrevers(str[1]), 1, 0);
	ft_str_arr_free(str);
}
