/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldtoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:00:20 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/04 17:00:21 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"
#include "header.h"

#define  TEST55
#define  ACC 5

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
char	*ft_ldtoa_final(long double ld, int accuracy);

/*  функция для округления числа */
void	ft_round_str_num(char *answer, int acc_round);

/* заносит в строку ответ целую часть числа в обратном направлении */
//void	ft_natural_part(p_list	*p)



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

/*  умножаем строку чаров на цифру */
void	ft_multiplic_str_num(char *str, int n)
{
	int		overfl;
	int		i;
	int		len;

	overfl = 0;
	i = 0;
	if (n >= '0')
		n = n - '0';
	len = ft_strlen(str);
	while (i < len || overfl > 0)
	{
		if (str[i] >= '0')
			str[i] = str[i] - '0';
		str[i] = str[i] * n + overfl;
		overfl = str[i] / 10;
		str[i] = str[i] % 10;
		str[i] = str[i] + '0';
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

/* не получилось исправить функцию
** надо добавить для предотвращения суммирования на больших степенях
** либо пропустить вайлом в начале
**if (str[i] != '0' || answer[i + shift] != '0' || overfl != 0)
**{
*/
/*
void	ft_summ_str_str(char *answer, char *str, int shift)
{
	int		overfl;
	int		i;
	int		len;
	int		k;

	overfl = 0;
	i = 0;
	k = 0;
	len = ft_strlen(str);
	while (k < len || overfl > 0)
	{
		if (answer[i + shift] == '.')
			shift++;
		if (answer[i + shift] >= '0')
			answer[i + shift] = answer[i + shift] - '0';
		answer[i + shift] = str[k] + answer[i + shift] + overfl;
		if (str[k])
			answer[i + shift] = answer[i + shift] - '0';
		overfl = answer[i + shift] / 10;
		answer[i + shift] = answer[i + shift] % 10;
		answer[i + shift] = answer[i + shift] + '0';
		if (str[k])
			k++;
		i++;
	}
}
*/




/*  умножаем строку чаров на строку */
void	ft_multiplic_str_str(char **answer, char *str1, char *str2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	k = ft_strlen(str1) + ft_strlen(str2);
	str = ft_strnew(k);
	if (*answer == NULL)
		*answer = ft_strnew(k);
	//ft_print_str(*answer);
	k = ft_strlen(str1);
	while (i < k)
	{
		ft_strcpy(str, str2);
		ft_multiplic_str_num(str, (int)str1[i]);
		ft_summ_str_str(*answer, str, i);
		ft_strclr(str);
		i++;
	}
	free(str);
}

/*  возводим строку чаров в строку чаров */
void	ft_strpower(char **answer, char *str, int power)
{
	char *s;

	*answer = ft_strdup(str);
	if (power < 0)
		*answer = ft_strcpy(*answer, "0");
	*answer = ft_strcpy(*answer, "1");
	while (power > 0)
	{
		if (power % 2)
		{
			s = NULL;
			ft_multiplic_str_str(&s, *answer, str);
			free(*answer);
			*answer = s;
			power--;
		}
		else
		{
			s = NULL;
			ft_multiplic_str_str(&s, str, str);
			ft_strcpy(str, s);
			ft_strdel(&s);
			power = power >> 1;
		}
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

/*  функция для округления числа */

void	ft_round_str_num(char *answer, int acc_round)
{
	char	*str;
	int		n;

	n = ft_strlen(answer);
	//printf("%s\n", answer);
	//printf("%c\n", answer[n - acc_round + 1]);
	if (answer[n - acc_round] > '4')
	{
		answer[n - acc_round] = '\0';
		ft_strrevers(answer);
		//printf("%s\n", answer);
		str = ft_strnew(n);
		str[0] = '1';
		//str = ft_strcpy(str, "1");
		//printf("%s\n", str);
		ft_summ_str_str(answer, str, 0);
		//printf("%s\n", answer);
		ft_strrevers(answer);
		free(str);
	}
	else
		answer[n - acc_round] = '\0';
}

/*  функция для округления числа по точности после запятой, нужно выправить */
///////////////////////////
void	ft_round_str_num2(char **answer, int accuracy)
{
	char	*str;
	int		n;

str = NULL;
	str = ft_strchr(*answer, '.');
	//printf("%s\n", str);
	str = !(str) ? *answer : str;
	//printf("%s\n", str);

	//printf("%s\n", *answer);
	printf("%c\n", str[accuracy + 1]);
	if (str[accuracy + 1] > '4')
	{
		str[accuracy + 1] = '\0';
		ft_strrevers(*answer);
		ft_putstr(*answer);
		ft_putchar('\n');
		n = ft_strlen(*answer) + 1;
		str = NULL;

		ft_putnbr(n);
		ft_putchar('\n');
		if (!(str = ft_strnew(n)))
		{
			ft_putchar('A');
			return ;
		}
		//str = ft_strcpy(str, "1");
		ft_putstr("BB");
		str[0] = '1';
		ft_putstr(str);
		ft_putchar('\n');
		//printf("%s\n", str);
		ft_summ_str_str(*answer, str, 0);
		//printf("%s\n", *answer);
		ft_strrevers(*answer);
		free(str);
	}
	else
		str[accuracy + 1] = '\0';
	str = ft_strdup(*answer);
	free(*answer);
	*answer = str;

}
///////////////////////////







/*  возможно это не нужно */
p_list	*ft_create_param(void)
{
	p_list	*p;

	if (!(p = (p_list	*)ft_memalloc(sizeof(p_list))))
		return(NULL);
	p->answer = NULL;
	p->minpow_2 = 0;
	p->pow_10 = 1;
	p->mask_nat = 0x0000000000000001l; //маска для побитового сдвига целой части
	p->mask_dec = 0x8000000000000000l; //маска для побитового сдвига дробной части
	return(p);
}

/* надо разделить на 2 функции или убрать лишние команды */
/* возвращает степень двойки из числа с типом данных long double */
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


	#ifdef TEST1
	ft_putstr(ft_bytes_to_bits((char *)(&(p->mask_dec)), sizeof(p->mask_dec), "__"));
	#endif
}


/*  в процессе ... */
char		*ft_ldtoa_final(long double ld, int accuracy)
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
		if (accuracy > 0)
			p->answer = ft_strjoin_free((p->answer), ".", 1, 0);
		ft_decimal_part(p, accuracy + 3);
		ft_round_str_num(p->answer, 3);
		//ft_num_stretch(&str[0], len);// тут ли оно должно быть расположено?
		ans = p->answer;
	}
	if (p->znak == -1 && ans[0] != 'n')
		ans = ft_strjoin_free("-", ans, 0, 1);
	free(p);
	return (ans);
}


/*  добавляет кучу пробелов слева или справа от числа в зависимости от знака "-" */
char	*ft_num_stretch_space(char *str, int len, int minus)
{
	int		n;
	char	*space;

	n = ft_strlen(str);
	if (len <= n)
		return (str);
	len = len - n;
	space = ft_strnew(len);
	ft_memset((void *)space, ' ', len);
	if (minus == 1)
		return(ft_strjoin_free(str, space, 1, 1));
	else
		return(ft_strjoin_free(space, str, 1, 1));
}

/*  определяет номер разряда первой цифры, если 0 - число равно 0  */
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

/*  функция для присоединения степени с буквой е к числу  */
char		*ft_ldtoa_final_e_3(char *str, int power)
{
	char end[20];
	char *str_power;
	char *end1;

	//ft_strncpy(end, "e+00", 6);
	if (power > 0)
		power--;
	else if (power < 0)
		{
			power = -power;
			end[1] = '-';

		//ft_strncpy(char *dest, const char *src, size_t n)
	str_power = ft_itoa(power);
	write(1, "error\n", 7);
//	if (power > 9)
//		end1 = ft_strdup("e+");
//	else
//		end1 = ft_strdup("e+0");
	write(1, "error\n", 7);
		//printf("%s\n%s\n", str, end);

	//end1 = ft_strjoin(end1, str_power);

	//free(str_power);
	write(1, "error\n", 7);
//	printf("%s\n%s\n", str, end1);
	//str = ft_strjoin_free(str, end, 1, 0);
	//str = ft_strjoin(str, end1);
	write(1, "error\n", 7);
	return (str);
}

/*  функция для обрезания строки до нужной точности и установкой точки
на втором знаке */
char		*ft_ldtoa_final_e_2(char *str, int power, int accuracy)
{
	char	*begin;
	int		len;


	//printf("%s\n", str);

	begin = ft_strnew(accuracy + 2 + ACC);
	ft_memset(begin, '0', accuracy + 2 + ACC);
	//printf("%s\n", begin);
	begin[1] = '.';
	//printf("%s\n", begin);
	ft_strrevers(str);
	//printf("%s\n", str);
	len = ft_strlen(str) - 1;
	while (len > 0 && str[len] == '0')
	{
		str[len] = '\0';
		len--;
	}
	//printf("%s\n", str);
	begin[0] = str[len];
	str[len] = '\0';
	ft_strrevers(str);
	//printf("%s\n", str);
	ft_memcpy((void *)(begin + 2), str, accuracy + ACC);
	if (accuracy == 0)
		begin[1] = '\0';
	//free(str);
	//printf("%s\n", begin);
	return (begin);
}

/*  это надо исправить
проверяем длину натуральной части
не является ли она 0,
из точности вычитаем длину натуральной части, если она не 0
и посылаем остаток в десятичную часть
потом сдвигаем часть с точкой
приставляем в конце букву е и степень
*/

char		*ft_ldtoa_final_e(long double ld, int accuracy)
{
	p_list	*p;
	char	*ans;
	int		power10;

	if (!(p = (p_list	*)ft_memalloc(sizeof(p_list))))
		return (0);
	write(1, "error7\n", 8);
	ft_param_of_ld(ld, p, accuracy);//inf , nan надо вернуть
	write(1, "error6\n", 8);
	ans = p->answer;
	power10 = 0;
	if (ans == 0)
	{
		ld = ld * p->znak;
		write(1, "error5\n", 8);
		power10 = ft_power_of_num(ld);//
		write(1, "error4\n", 8);
		if (power10 > 0)
			ft_natural_part(p);
		printf("%d\n", power10);
		printf("1_%s\n", p->answer);
		write(1, "error3\n", 8);
		if (accuracy + 3 >= power10 || power10 == 0)
			ft_decimal_part(p, accuracy - power10 + ACC);
		//ft_round_str_num2(p->answer, accuracy);
		//ft_round_str_num(p->answer, 3);
		write(1, "error2\n", 8);
	}
	printf("1_%s\n", p->answer);
	ans = ft_ldtoa_final_e_2((p->answer), power10, accuracy);
	write(1, "error1\n", 8);
	printf("%s\n", ans);
	ft_round_str_num2(&ans, accuracy); //сега
	write(1, "error8\n", 8);
	//ans = ft_ldtoa_final_e_3(ans, power10);
	//if (p->znak == -1 && ans[0] != 'n')
	//	ans = ft_strjoin_free("-", ans, 0, 1);
	//free(p);
	return (ans);
}



/*  добавляет кучу нулей слева от числа в зависимости от знака "0" */
char	*ft_num_stretch_nuls(char *str, int len, int plus)
{
	int		n;
	char	*nuls;
	char	znak[3];

	znak[0] = '0';
	znak[1] = '\0';
	n = ft_strlen(str) + 1;
	if (str[0] == '-')
	{
		znak[0] = '-';
		str[0] = '0';
	}
	else if (plus > 0)
		znak[0] = (plus == 1) ? '+' : ' ';
	if (len > n)
	{
		len = len - n + 1;
		nuls = ft_strnew(len);
		ft_memset((void *)nuls, '0', len);
		nuls[0] = znak[0];
		return (ft_strjoin_free(nuls, str, 1, 1));
	}
	str = ft_strjoin_free(znak, str, 0, 1);
	return (str);
}


int main(void)
{
	int t = 15;
	int len = 20;
	char *str;
	long double ld = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;
	long *ptr;
	double f;
	//ld = -0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001195999125990000000000990999;//8.00357;
	//ld = 0;
	//ld = -10.01;
	//*((long *)(&ld)) = 0xf000000000000000l;
	//ft_putstr(ft_bytes_to_bits((char *)(&ld), sizeof(ld), "__"));
	//ilon_mask = (long *)(&ld);
	//*ilon_mask = *ilon_mask | 0x4000000000000000;

	//printf("%s\n", ft_ldtoa3(ld, t));

	//printf("%d\n", ft_power_of_num(ld));
	//ld = ld * ld * ld * ld;
	//ld = ld * ld * ld;
	//ld = ld * ld;
	//ld = ld * ld;
	//ld = ld * ld;
	//ld = ld * 0;
	//ld = 0/0;
	//f = nan;
/*
	ptr = ((long *)(&ld) + 1);
	*ptr = *ptr | 0x0000000000008000l;
*/

	//ptr = ((long *)(&ld));
	//*ptr = 0xc100000000000000l;



/*  запуск вывода числа с плавающей точкой */
	//str = ft_ldtoa_final(ld, t);
	//printf("%s\n", str);

/*  запуск вывода числа с плавающей точкой  с флагами пробелов, минусом, плюсом и 0*/
	//str = ft_num_stretch_nuls(str, len, 2); //работает
	//str = ft_num_stretch_space(str, len, 1); //работает
	//printf("%s\n", str);

	//printf("%d\n", ft_power_of_num(ld));

	//printf("%20.*Le\n", t, ld);
	//printf("%#- 20.*Lf\n", t, ld);

/*  запуск вывода числа с плавающей точкой в логарифмическом виде */
	// str = ft_ldtoa_final_e(ld, t);
	// printf("%s\n", str);
	// printf("%.*Le\n", t, ld);


	#ifdef TEST
	ft_putstr(ft_bytes_to_bits((char *)(&(ld)), sizeof(ld), "__"));
	#endif


	union types
	{
	  float f;
	  struct	s_ma
	  {
		  unsigned int m:23;
		  unsigned int e:8;
		  unsigned int s:1;
	  }			ma;
	  int   i;
	  char 	chr;
	};

	union types values;
	values.f = 64.0;

	char *chrr;

	//chrr = &(values.chr);
	//printf("%hhx ", *(chrr + 3));
	//printf("%hhx ", *(chrr + 2));
	// printf("%hhx ", *(chrr + 1));
	// printf("%hhx ", *chrr);

	printf("%d ", values.ma.s);
	printf("%d ", values.ma.e);
	printf("%d ", values.ma.m);

	ft_putstr(ft_bytes_to_bits((char *)(&(values.f)), sizeof(values.f), "__"));



	//ft_putnbr(*(a + 1));


	//t = ((*((int *)(&ld) + 2)) & 0x00007fff) - 16383;
	//printf("%d\n", t);

	return (0);
}
