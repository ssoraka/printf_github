/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:32:43 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/30 16:32:44 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"


double	ft_power_double(long double nb, int power);
int		ft_power_of_ld(long double ld);
void	ft_decimal_part(int min_power2, unsigned long bits, char **str, int accuracy);
void	ft_natural_part(int max_power2, unsigned long bits, char **str);

char		*ft_itoa_base(int num, int base)
{
	char	*str;
	char	temp[2];
	int		znak;
	unsigned int n;

	n = num;
	znak = 1;
	if (base > 16 || base < 2)
		return (0);
	if (base == 10 && num < 0)
		znak = -1;
	temp[1] = '\0';
	str = ft_strnew(0);
	while (n >= base)
	{
		temp[0] = n % base < 10 ? n % base + '0' : n % base + 'a' - 10;
		str = ft_strjoin_free(temp, str, 0, 1);
		n = n / base;
	}
	temp[0] = n % base < 10 ? n % base + '0' : n % base + 'a' - 10;
	str = ft_strjoin_free(temp, str, 0, 1);
	if (znak < 0)
		str = ft_strjoin_free("-", str, 0, 1);
	return (str);
}

/*
char		*ft_ldtoa(long double ld, int accuracy)
{
	char		*str;
	int			power;
	int			znak;
	char		chr;
	size_t		i;
	size_t		j;
	long double	num;
	long double	num2;

	power = ft_power_of_ld(ld);
	power = power < 0 ? 1 : power;
	znak = (1 / ld < 0) ? 1 : 0;
	ld = (ld < 0) ? -ld : ld;
	i = 0;
	if (!(str = ft_strnew(power + znak + accuracy + 1)))
		return (NULL);
	if (znak == 1)
		str[i++] = '-';
	num = ft_power_double(10, power);
	//printf("%Lf ___ %d\n", num, power);
	num2 = 0;
	*//*
	ld = ld / num;
	while (i <= power + znak + 1 + accuracy)
	{
		chr = (char)ld;
		//printf("%d\n", chr);
		str[i] = chr + '0';
		//printf("%Lf\n", ld);
		ld = (ld - chr) * 10;
		//printf("%Lf\n", num2);
		i++;
		if (i == power + znak + 1)
			str[i++] = '.';
	}
*/

/*
	while (i <= power + znak + 1 + accuracy)
	{
		chr = (char)((ld - num2) / num);
		//printf("%d\n", chr);
		str[i] = chr + '0';
		//printf("%Lf\n", ld);
		num2 = num2 + (int)chr * num;
		//printf("%Lf\n", num2);
		num = num / 10;
		i++;
		if (num == 0.1)
			str[i++] = '.';
	}

	//printf("%Lf\n", num);
	*//*
	if (accuracy > 0)
		str[i++] = '.';
	j = 0;
	while (j < accuracy)
	{
		chr = (char)(ld * 10);
		str[i + j] = chr + '0';
		ld = ld * 10 - chr;
		j++;
	}*//*
	return (str);
}*/

int		ft_power_of_ld2(long double ld)
{
	int		*mask;
	unsigned int		power;

	mask = (int *)(&ld) + 2;
	power = *mask  & 0x00007fff;
	power = power - 16383;
	if (power == -16383)
		return (0);
	return (power);
}

void	ft_print_str(char *str)
{

	ft_strrevers(str);

	printf("%s\n", str);

	ft_strrevers(str);

}

/*  делим строку чаров на цифру */
void	ft_division_str_num(char *str, int n, int accuracy)
{
	int		overfl;
	int		i;

	overfl = 0;
	i = 0;
	if (n >= '0')
		n = n - '0';
	while (i < accuracy)
	{
		if (str[i] >= '0')
			str[i] = str[i] - '0';
		str[i] = str[i] + overfl;
		overfl = (str[i] % n) * 10;
		str[i] = str[i] / n;
		str[i] = str[i] + '0';
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
		if (answer[i + shift] >= '0')
			answer[i + shift] = answer[i + shift] - '0';
		if (str[i] >= '0')
			str[i] = str[i] - '0';
		answer[i + shift] = str[i] + answer[i + shift] + overfl;
		overfl = answer[i + shift] / 10;
		answer[i + shift] = answer[i + shift] % 10;
		answer[i + shift] = answer[i + shift] + '0';
		if (str[i] < '0')
			str[i] = str[i] + '0';
		i++;
	}
}

//ft_multiplic_str_str(&s, *str, *str);

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








char		*ft_ldtoa3(long double ld, int accuracy)
{
	char		**str;
	int			power10;
	int			power2;
	int			i;
	unsigned long	bits;
	unsigned long	mask;
	int			power_bits;


	power2 = ft_power_of_ld2(ld);
	power10 = ft_power_of_ld(ld) + 3; //уточнить формулу
	ld = (1 / ld < 0) ? -ld : ld;// добавить знак



	//вычленяем максимальное число степени двойки
	bits = *((long *)(&ld)) & 0xffffffffffffffffl;
	//printf("%s\n", ft_bytes_to_bits((char *)(&bits), sizeof(bits), "__"));
	//находим минимальное число степени двойки
	power_bits = power2 - 8 * 8 + 1;
	//printf("%d\n", power_bits);

	char		**str_divis;
	if (!(str_divis = ft_str_arr_new(2, accuracy)))
		return (NULL);

	str_divis[0][0] = (power_bits < 0) ? '5' : '0';
	//ft_decimal_part(power_bits, bits, str_divis, accuracy);

	if (power_bits < -63)
		ft_decimal_part(power_bits, bits, str_divis, accuracy);
	else
		ft_memset(str_divis[1], '0', accuracy);
	//printf("0.%s\n", str_divis[1]);
	//printf("%s\n", str_divis[2]);

/*
	str[4][0] = (power_bits > 0) ? '5' : '0';
	mask = 0x0000000000000001l;

	i = power_bits;
	while (i < 0 && mask != 0)
	{
		i++;
		mask = mask << 1;
	}


	i = -1;
	while (i > power_bits)
	{
		ft_division_str_num(str[4], 2, accuracy);
		if (i == power_bits)
		{

		if ((bits & 0x0000000000000001l) == 1)
			ft_summ_str_str(str[1], str[0], 0);
		power_bits++;
		bits = bits >> 1;
	}
*/

	if (!(str = ft_str_arr_new(2, power10)))
		return (NULL);
	str[0][0] = (power2 >= 0) ? '1' : '0';
	if (power2 >= 0)
		ft_natural_part(power2, bits, str);
	else
		str[1][0] = '0';

/* надо вставить функцию для возведения числа str[0] в степень power_bits */
/*
	while (power_bits < 0)
	{
		power_bits++;
		bits = bits >> 1;
	}
	i = 0;
	while (i <= power2)
	{
		if (i > 0)
			//ft_multiplic_str_num(str[0], 2);
			ft_summ_str_str(str[0], str[0], 0);

		if (i == power_bits)
		{
			if ((bits & 0x0000000000000001l) == 1)
				ft_summ_str_str(str[1], str[0], 0);
			power_bits++;
			bits = bits >> 1;
		}
		i++;
	}
*/
	ft_strrevers(str[1]);
	printf("%s.%s\n", str[1], str_divis[1]);
	return (NULL);
	return (str[1]);
}


void	ft_natural_part(int max_power2, unsigned long bits, char **str)
{
	int min_power2;
	unsigned long mask;
	int i;

	min_power2 = max_power2 - 8 * 8 + 1;
	mask = 0x0000000000000001l;
	while (min_power2 < 0)
	{
		min_power2++;
		mask = mask << 1;
	}
	i = 0;
	while (i <= max_power2)
	{
		if (i > 0)
			ft_summ_str_str(str[0], str[0], 0);
		if (i == min_power2)
		{
			if ((bits & mask) != 0)
				ft_summ_str_str(str[1], str[0], 0);
			min_power2++;
			mask = mask << 1;
		}
		i++;
	}

}





void	ft_decimal_part(int min_power2, unsigned long bits, char **str, int accuracy)
{
	int max_power2;
	unsigned long mask;
	int i;

	mask = 0x0000000000000001l;
	max_power2 = min_power2;
	while (max_power2 < -1 && max_power2 - min_power2 < 63)
	{
		max_power2++;
		mask = mask << 1;
	}
	//printf("%d ___ %d\n",min_power2, max_power2);
	i = -1;
	while (i > min_power2)
	{
		if (i == max_power2)
		{
			if ((bits & mask) != 0)
			{
				ft_strrevers(str[1]);
				ft_strrevers(str[0]);
				ft_summ_str_str(str[1], str[0], 0);
				ft_strrevers(str[1]);
				ft_strrevers(str[0]);
			}
			max_power2--;
			mask = mask >> 1;
		}

		ft_division_str_num(str[0], 2, accuracy);
		i--;
	}
}














char		*ft_itoa_float(long double n, int razr)
{
	char	*str;
	char	temp[2];
	int		znak;
	int		i;

	i = 0;
	znak = 1;
	temp[1] = '\0';
	if (1 / n < 0)
		znak = -1;
	str = ft_itoa((int)(n * znak));
	n = (n - (long)n) * znak;
//	if (razr > 0)
	str = ft_strjoin_free(str, ".", 1, 0);
	while (i++ < razr + 1)
	{
		n = n * 10;
		temp[0] = '0' + (long)(n);
		str = ft_strjoin_free(str, temp, 1, 0);
		n = (n - (long)n);
	}
//	if ((int)(n * 10) > 4)
//		ft_round_num(str, razr)
//		str = str;
	if (znak < 0 && str[0] != '-')
		str = ft_strjoin_free("-", str, 0, 1);
	return (str);
}




/*
char		*ft_itoa_float1(double n, int razr)
{
	char	temp[2];
	char	*str;
	int		i;

	i = 0;
	if (razr == 0)
		return (NULL);
	temp[1] = '\0';
	str = ft_strdup(".");
	while (i < razr)
	{
		n = n * 10;
		temp[0] = '0' + (n / 1);
		str = ft_strjoin_free(str, temp, 1, 0);
		n = (n - (long int)n);
		i++;
	}
	return (str);
}
*/

/*
char		*ft_itoa_float(double n, int razr)
{
	int		i;
	char	*str;
	char	temp[2];
	int		flag;

	i = 0;
	flag = 0;
	temp[1] = '\0';
	str = ft_strdup(".");
	while (i < razr)
	{
		n = n * 10;
		temp[0] = '0' + (n / 1);
		str = ft_strjoin_free(str, temp, 1, 0);
		n = (n - (int)n);
		i++;
	}
	if ((int)(n * 10) > 4)
		flag = 1;
	while (flag == 1)
	{
		if (str[i]) == '9';
			str[i] = 0;
		else
		{
			str[i]++;
			flag = 1;
		}
		i--;
	}
	return (str);
}
*/


int		ft_power_of_ld(long double ld)
{
	int		*mask;
	unsigned int		power;

	mask = (int *)(&ld) + 2;
	power = *mask  & 0x00007fff;
	//printf("%d\n", power);
	//power = (power * 10000 / 33219);
	if (power <= 16383)
		return (0);
	//znak = ft_znak(power - 16383);
	power = (power - 16383);
	printf("%d\n", power);
	power = (power * 10000) / 33219;
	//printf("%d\n", power);
	//power = power -4931;
	if (power == -4931)
		return (0);
	return (power);
		//*mask = *mask & 0x00007fff;
	//mask = ((int *)(&ld) + 0);
	//power = (*mask & 0x7fffc000);// >> 0;//) - 1023) * 100 / 332;


	//printf("%s\n", ft_bytes_to_bits(chr, 32, "__"));
	/*
	char	*chr;
	chr = (char *)(&ld);
	printf("%s\n", ft_bytes_to_bits((char *)(mask), 4, "__"));
	printf("%s\n", ft_bytes_to_bits((char *)(&power), 4, "__"));
	return (power);
	*/
}


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



int main(void)
{
	int t = 200;
	char *str1 = "123";
	char *str2 = "123";
	char *s;
	int *t1;
	void *p;
	double f1 = -16.0;
	double f2 = 0.000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000;
	double *f3 = &f1;
	long *ilon_mask;
	double black_power;
	int white_power;
	long double ld = 00000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;
	//ld = 0.0010;
	ld = 0.0625;
	ld = 1.0;

	//ilon_mask = (long *)(&ld);
	//*ilon_mask = *ilon_mask | 0x4000000000000000;

	//printf("%s\n", ft_ldtoa3(ld, t));
	ft_ldtoa3(ld, t + 2);
	printf("%.*Lf\n", t, ld);

	printf("%d\n", sizeof(long double**));

	//ft_summ_str_str(str, str, 0);

	//str1 = ft_strnew(10000);
	//str2 = ft_strnew(10000);
	//str2[0] = '5';

	//str2[2] = '1';

	//ft_strrevers(str2);
	//printf("%s в степени %d\n", str2, 7000);
	//ft_strrevers(str2);

	//ft_strpower(&str1, str2, 7000);

	//ft_strrevers(str1);

	//printf("%s\n", str1);
	//printf("%d\n", ft_strlen(str1));




/*
	int n = 10;

	while (n > 0)
	{
		ft_division_str_num(str2, 2, 50);
		n--;
	}

	printf("%s\n", str2);

	ld = 0.000488281250;
	printf("%.5Lf\n", ld);
*/
	//ft_multiplic_str_str(&s, str1, str2);
	//printf("%s\n", s);

	//printf("%d\n", (int)(ld - ld / 10));
/*
	s = ft_itoa_base(t, 8);
	printf("%s\n", s);
	printf("%o\n", t);
	free(s);
*/

	//s = ft_itoa_float(ld,t);

	//printf("%s\n", s);
	//printf("%.*Lf\n", t, ld);

	//printf("%lu\n", sizeof(long double));

//	ld = ld * ld * ld * ld * ld * ld * ld * ld * f2 * f2 * 100000000000;
//	ld = ld * ld;
	//f1 = ld;

//	printf("%d\n", ft_power_of_ld(ld));
//	printf("%Le\n", ld);

//	printf("%lu\n",(long)f1);
//	printf("%lu\n",sizeof(short));

/*
	f2 = 1 / f1;
	if (f2 > 0)
		printf("%s\n", "знак +");
	if (f2 < 0)
		printf("%s\n", "знак -");

	printf("%lu\n", sizeof(long));
*/
	//printf("%s\n", ft_bytes_to_bits((char *)(&ld), sizeof(ld), "__"));
//	printf("%s\n", ft_bytes_to_bits((char *)(&f1), sizeof(f1), "__"));

//	f1 = f1 / 10;
//	printf("%s\n", ft_bytes_to_bits((char *)(&f2), sizeof(f2), "__"));
//	f2 = f2 / 10;
//	printf("%s\n", ft_bytes_to_bits((char *)(&f2), sizeof(f2), "__"));
/*	f1 = f1 / 10;
	printf("%s\n", ft_bytes_to_bits((char *)(&f1), sizeof(f1), "__"));

	t = atoi("21");
*/

	//ft_bzero(((char *)(&f1) + 6), 2);
	//printf("%.0f\n", f1);
//	printf("%.50e\n", f1);

	//printf("%s\n", ft_bytes_to_bits((char *)(&f1), sizeof(f1), "__"));

	//f1 = *(double *)((int *)(&f1));// & 0xfffffffffffff001);
	//ilon_mask = ((int *)(&f1)) + 1;

	//white_power = (((*ilon_mask & 0x7ff00000) >> 20) - 1023) * 100 / 332;
	//black_power = ((((*ilon_mask & 0x7ff00000) >> 20) - 1023) * 100 - white_power * 332) / 100 ;
	//*ilon_mask = (*ilon_mask & 0x800fffff) | 0x3ff00000;
	//black_power = ft_power_double(10, white_power);
	//printf("%.50e\n", black_power);

//	printf("%d\n", white_power);

/*
	while (white_power != 0)
	{
		f1 = f1 / (int)10;
		white_power--;
	}
*/
//	f1 = f1 / ft_power_double(10, white_power);



/*
	printf("%s\n", ft_bytes_to_bits((char *)(&white_power), 4, "__"));
	printf("%s\n", ft_bytes_to_bits((char *)(&f1), 6, ""));
*/
	//printf("%.50f   в степени   %d\n", f1,  white_power);

	return 0;
}
