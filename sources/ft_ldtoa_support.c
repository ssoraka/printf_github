/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:45:25 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:45:25 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	определение степени 10 для первой значащей цифры
*/

int		ft_power_of_num(long double ld)
{
	int		znak;
	int		count;

	count = 0;
	znak = (*((long *)(&ld) + 1) & 0x0000000000008000l) == 0 ? 1 : -1;
	ld = ld * znak;
	if (ld >= 1)
		while (ld >= 1)
		{
			ld = ld / 10;
			count++;
		}
	else if (ld > 0 && ld < 1)
		while (ld < 1)
		{
			ld = ld * 10;
			count--;
		}
	return (count);
}

/*
**	функция для округления числа по точности после запятой
*/

void	ft_round_str_num(char **answer, int accur)
{
	char	*str;
	int		n;

	n = 1;
	str = ft_strchr(*answer, '.');
	str = !(str) ? *answer : str;
	if (str[accur + 1] == '5')
	{
		while (str[accur + 1 + n])
		{
			if (str[accur + 1 + n] != '0')
			{
				str[accur + 1]++;
				break ;
			}
			n++;
		}
		if (str[accur + 1] == '5' && ((str[accur] != '.' && (str[accur] % 2)) ||
			(str[accur] == '.' && (str[accur - 1] % 2) == 1)))
			str[accur + 1]++;
	}
	if (str[accur + 1] > '5')
		ft_round_up(*answer, str + accur);
	else
		str[accur + 1] = '\0';
}

void	ft_round_up(char *str, char *accuracy)
{
	char	*add;

	*(accuracy + 1) = '\0';
	*(accuracy + 2) = '\0';
	ft_strrevers(str);
	if (!(add = ft_strnew(ft_strlen(str) + 1)))
		return ;
	add[0] = '1';
	ft_summ_str_str(str, add, 0);
	ft_strrevers(str);
	free(add);
}

/*
**	функция для стирания нулей с конца числа
*/

void	ft_increase_power(char *str, int *power)
{
	if (str[1] != '.')
	{
		str[2] = str[1];
		str[1] = '.';
		str[ft_strlen(str) - 1] = '\0';
		(*power)++;
	}
}

/*
**	функция для стирания нулей с конца числа
*/

void	ft_clear_null(char *str, int type_g)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (type_g == 1)
	{
		while (len > 0 && str[len] == '0')
		{
			str[len] = '\0';
			len--;
		}
	}
	if (str[len] == '.')
		str[len] = '\0';
}
