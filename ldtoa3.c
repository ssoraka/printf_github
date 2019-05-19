/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldtoa2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:34:01 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/08 15:34:01 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"
#include "header.h"

#define  TEST55
#define  ACC 20

/* прибавляем строку чаров к другой строке */
void	ft_summ_str_str(char *answer, char *str, int shift);
/*  умножаем строку чаров на строку */
void	ft_multiplic_str_str(char **answer, char *str1, char *str2);
/*  делим строку чаров на цифру */
void	ft_division_str_num(char *str, int n, int accuracy);
/*  умножаем строку чаров на цифру */
void	ft_multiplic_str_num(char *str, int n);
/*  возводим строку чаров в строку чаров */
void	ft_strpower(char **answer, char *str, int power);
/*  удалить, только для вывода на экран */
void	ft_print_str(char *str);
/*  в процессе... */
char	*ft_ldtoa_final(long double ld, int accuracy, int type_g);

/*  функция для округления числа */
void	ft_round_str_num(char *answer, int acc_round);

/*  функция для стирания 0 в конце строки */
void	ft_clear_null(char *str, int type_g, int *power);

/*  удалить, только для вывода на экран */
void	ft_print_str(char *str)
{
	ft_strrevers(str);
	ft_putendl(str);
	ft_strrevers(str);
}

/*  делим строку чаров на цифру */
void	ft_division_str_num(char *str, int n, int accuracy)
{
	int		overfl;
	int		i;
	long 	*l;

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

/* прибавляем строку чаров к другой строке */
void	ft_summ_str_str(char *answer, char *str, int shift)
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


/* заносит в строку ответ целую часть числа в обратном направлении */
void	ft_natural_part(p_list	*p)
{
	int i;
	char **str;

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


/* заносит в строку ответ дробную часть числа в прямом порядке */
void	ft_decimal_part(p_list	*p, int accuracy)
{
	int i;
	char **str;

	str = ft_str_arr_new(2, accuracy);
	ft_memset(str[0], '0', accuracy);
	str[0][0] = (p->minpow_2 > -1) ? '0' : '5';
	ft_memset(str[1], '0', accuracy);
	i = -1;
	//printf("%d\n", p->dmaxpow_2);
	while (i >= p->minpow_2)
	{
		if (i == p->dmaxpow_2)
		{
			//ft_putstr("Текущий бит = ");
			//int a = (p->ld_bits & p->mask_dec) != 0 ? 1 : 0;
			//ft_putnbr(a);
			//ft_putstr("\n");
			if ((p->ld_bits & p->mask_dec) != 0)
			{
				ft_strrevers(str[0]);
				ft_summ_str_str(str[1], str[0], 0);
				ft_strrevers(str[0]);
				//ft_putstr("общая сумма:\n");
				//ft_putstr(str[0]);///dsdfsdfsdf
				//ft_putstr("\n");
				//ft_print_str(str[1]);///dsdfsdfsdf
			}
			p->dmaxpow_2--;
			p->mask_dec = p->mask_dec >> 1;
		}
		ft_division_str_num(str[0], 2, accuracy);
		//ft_putstr(str[0]);///dsdfsdfsdf
		//ft_putstr("\n");
		i--;
	}
	ft_strrevers(str[1]);
	p->answer = ft_strjoin_free((p->answer), str[1], 1, 0);
	ft_str_arr_free(str);
}


void	ft_param_of_ld(long double ld, p_list	*p, int accuracy)
{

	p->answer = NULL;
	p->maxpow_2 = ((*((int *)(&ld) + 2)) & 0x00007fff) - 16383; //максимальная степень двойки
	p->znak = (*((long *)(&ld) + 1) & 0x0000000000008000l) == 0 ? 1 : -1;
	p->ld_bits = *((long *)(&ld)) & 0xffffffffffffffffl; //само число
	if (p->maxpow_2 == -16383) // число равно 0
	{
		p->minpow_2 = 0;
		p->pow_10 = 1;
		return ;
	}
	if (p->maxpow_2 == 16384)
	{
		p->answer = (p->ld_bits == 0x8000000000000000l) ? ft_strdup("inf") : ft_strdup("nan");
		return ;
	}
	p->minpow_2 = p->maxpow_2 - 8 * 8 + 1; //минимальная степень двойки
	p->pow_10 = (p->maxpow_2 < 0) ? 0 : ((p->maxpow_2 * 10000) / 33219) + 3; //число разрядов целой части
	p->mask_nat = 0x0000000000000001l; //маска для побитового сдвига целой части
	p->nminpow_2 = p->minpow_2; //минимальный
	while (p->nminpow_2 < 0)
	{
		p->nminpow_2++;
		p->mask_nat = p->mask_nat << 1;
	}
	p->mask_dec = (p->mask_nat == 0) ? 0x8000000000000000l : p->mask_nat >> 1; //маска для побитового сдвига дробной части
	p->dmaxpow_2 = (p->maxpow_2 > -1) ? -1 : p->maxpow_2;
	p->accur = accuracy;

}

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

/*  функция для обрезания строки до нужной точности и установкой точки
на втором знаке */
char		*ft_ldtoa_final_e_2(char *str, int power, int accuracy)
{
	char	*begin;
	int		len;

	begin = ft_strnew(accuracy + 2 + ACC);
	ft_memset(begin, '0', accuracy + 2 + ACC);
	begin[1] = '.';
	ft_strrevers(str);
	ft_clear_null(str, 1, 0);
	//len = ft_strlen(str) - 1;
	// while (len > 0 && str[len] == '0')
	// {
	// 	str[len] = '\0';
	// 	len--;
	// }
	len = ft_strlen(str) - 1;
	begin[0] = str[len];
	str[len] = '\0';
	ft_strrevers(str);
	if (power != 0)
		ft_memcpy((void *)(begin + 2), str, accuracy + ACC);
	free(str);
	return (begin);
}

/*  функция для округления числа по точности после запятой, нужно выправить */
void	ft_round_str_num2(char **answer, int accuracy, int type_g)
{
	char	*str;
	int		n;

	//printf("%s\n", *answer);
	str = ft_strchr(*answer, '.');
	str = !(str) ? *answer : str;
	if (str[accuracy + 1] > '4')// && (type_g == 0 || (type_g == 1 && str[accuracy] > '0')))
	{
		//printf("%s\n", str);
		str[accuracy + 1] = '\0';
		str[accuracy + 2] = '\0';
		ft_strrevers(*answer);
		if (!(str = ft_strnew(ft_strlen(*answer) + 1)))
			return ;
		str[0] = '1';
		//printf("%s\n", *answer);
		//printf("%s\n", str);
		ft_summ_str_str(*answer, str, 0);
		ft_strrevers(*answer);
		free(str);
	}
	else
		str[accuracy + 1] = '\0';
}

void	ft_clear_null(char *str, int type_g, int *power)
{
	int		len;

	if (str[1] != '.' && power != 0)
		{
			str[2] = str[1];
			str[1] = '.';
			str[ft_strlen(str) - 1] = '\0';
			(*power)++;
		}
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


char		*ft_ldtoa_final_e_3(char *str, int power)
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

/*  для чисел с индексом e  */
char		*ft_ldtoa_final_e1(long double ld, int accuracy, int type_g)
{
	p_list	*p;
	char	*ans;
	int		power10;

	if (!(p = (p_list	*)ft_memalloc(sizeof(p_list))))
		return (0);
	ft_param_of_ld(ld, p, accuracy);//inf , nan надо вернуть
	ans = p->answer;
	if (ans == 0)
	{
		ld = ld * p->znak;
		power10 = ft_power_of_num(ld);//
		if (power10 > 0)
			ft_natural_part(p);
		if (accuracy + ACC >= power10 || power10 == 0)
			ft_decimal_part(p, accuracy - power10 + ACC);
		ans = ft_ldtoa_final_e_2((p->answer), power10, accuracy);
		ft_round_str_num2(&ans, accuracy, type_g); //сега
		ft_clear_null(ans, type_g, &power10);
		ans = ft_ldtoa_final_e_3(ans, power10);
	}
	if (p->znak == -1 && ans[0] != 'n')
		ans = ft_strjoin_free("-", ans, 0, 1);
	free(p);
	return (ans);
}

/*  для чисел с индексом f  */
char		*ft_ldtoa_final(long double ld, int accuracy, int type_g)
{
	p_list	*p;
	char	*ans;

	p = (p_list	*)ft_memalloc(sizeof(p_list));
	ft_param_of_ld(ld, p, accuracy);//inf , nan надо вернуть
	ans = p->answer;
	if (ans == 0)
	{
		ld = ld * p->znak;
		ft_natural_part(p);
		p->answer = ft_strjoin_free((p->answer), ".", 1, 0);
		ft_decimal_part(p, accuracy + ACC);
		ans = p->answer;
		ft_round_str_num2(&ans, accuracy, type_g);
		ft_clear_null(ans, type_g, 0);
	}
	if (p->znak == -1 && ans[0] != 'n')
		ans = ft_strjoin_free("-", ans, 0, 1);
	free(p);
	return (ans);
}

char		*ft_ldtoa_final_g(long double ld, int accuracy)
{
	int		power10;
	char	*str;

	power10 = ft_power_of_num(ld);//
	power10 = accuracy - power10;
	if (accuracy == 0)
		accuracy++;
	if (power10 >= 0)
		str = ft_ldtoa_final(ld, power10, 1);
	else
		str = ft_ldtoa_final_e1(ld, accuracy - 1, 1);
	return (str);
}
