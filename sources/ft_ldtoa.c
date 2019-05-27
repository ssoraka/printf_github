/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:42:32 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:42:32 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	вывод чисел ld с плавающей точной с индексом g
**	точностью accuracy после зпт.
*/

char		*ft_ldtoa_g(long double ld, int accuracy)
{
	int		power10;
	int		znak;
	int		len;
	char	*str;

	znak = 1;
	power10 = ft_power_of_num(ld);
	if (power10 < 0)
	{
		power10 = -power10;
		znak = -1;
	}
	if (accuracy == 0)
		accuracy++;
	len = accuracy - power10;
	if (len >= 0 && znak == 1)
		str = ft_ldtoa_f(ld, len, 1);
	else if (znak == 1)
		str = ft_ldtoa_e(ld, accuracy - 1, 1);
	else
		str = ft_ldtoa_f(ld, power10 + accuracy - 1, 1);
	if (len >= 0 && znak == 1)
		str = ft_plug(str, accuracy);
	return (str);
}

/*
**	вывод чисел ld с плавающей точной с индексом e (десятичная степень)
**	точностью accuracy после зпт.
*/

char		*ft_ldtoa_e(long double ld, int accuracy, int type_g)
{
	t_plist	*p;
	char	*ans;
	int		power10;

	p = ft_create_param(accuracy, ld);
	ans = p->answer;
	if (ans == 0)
	{
		ld = ld * p->znak;
		power10 = ft_power_of_num(ld);
		if (power10 > 0)
			ft_natural_part(p);
		if (accuracy + ACC >= power10 || power10 == 0)
			ft_decimal_part(p, accuracy - power10 + ACC);
		ans = ft_ldtoa_e_shift_point((p->answer), power10, accuracy);
		ft_round_str_num(&ans, accuracy);
		ft_increase_power(ans, &power10);
		ft_clear_null(ans, type_g);
		ans = ft_ldtoa_e_adde(ans, power10);
	}
	if (p->znak == -1 && ans[0] != 'n')
		ans = ft_strjoin_free("-", ans, 0, 1);
	free(p);
	return (ans);
}

/*
**	вывод чисел ld с плавающей точной с индексом f
**	точностью accuracy после зпт. и округлением нулей в конце type_g
*/

char		*ft_ldtoa_f(long double ld, int accuracy, int type_g)
{
	t_plist	*p;
	char	*ans;

	p = ft_create_param(accuracy, ld);
	ans = p->answer;
	if (ans == 0)
	{
		ld = ld * p->znak;
		ft_natural_part(p);
		p->answer = ft_strjoin_free((p->answer), ".", 1, 0);
		ft_decimal_part(p, accuracy + ACC);
		ans = p->answer;
		ft_round_str_num(&ans, accuracy);
		ft_clear_null(ans, type_g);
	}
	if (p->znak == -1 && ans[0] != 'n')
		ans = ft_strjoin_free("-", ans, 0, 1);
	free(p);
	return (ans);
}

/*
**	добавляет e с десятичной степенью к числу
*/

char		*ft_ldtoa_e_adde(char *str, int power)
{
	char end[20];
	char *str_power;

	ft_strncpy(end, "e+00", 10);
	if (power > 0)
		power--;
	else if (power < 0)
	{
		power = -power;
		end[1] = '-';
	}
	str_power = ft_itoa(power);
	if (power > 9)
		end[2] = '\0';
	else
		end[3] = '\0';
	ft_strcat(end, str_power);
	free(str_power);
	str = ft_strjoin_free(str, end, 1, 0);
	return (str);
}

/*
**	функция для обрезания строки до нужной точности и установкой точки
**	на втором знаке
*/

char		*ft_ldtoa_e_shift_point(char *str, int power, int accuracy)
{
	char	*begin;
	int		len;

	begin = ft_strnew(accuracy + 2 + ACC);
	ft_memset(begin, '0', accuracy + 2 + ACC);
	begin[1] = '.';
	ft_strrevers(str);
	ft_clear_null(str, 1);
	len = ft_strlen(str) - 1;
	begin[0] = str[len];
	str[len] = '\0';
	ft_strrevers(str);
	if (power != 0)
		ft_memcpy((void *)(begin + 2), str, accuracy + ACC);
	free(str);
	return (begin);
}
