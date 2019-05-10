/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:21:33 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/08 20:21:34 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"

char		ft_itochr(int num)
{
	if (num < 10)
		return (num + '0');
	if (num < 16)
		return (num - 10 + 'a');
	return (0);
}


char	*ft_print_pointer(void *ptr)
{
	union types
	{
		struct	s_ma
		{
			unsigned int m:4;
			unsigned int e:4;
		}			ma;
		char 	chr;
	};


	char	str[15];
	int		i;
	char	*temp;

	union types values;
	temp = (char *)(&ptr);
	i = 0;
	str[0] = '0';
	str[1] = 'x';
	str[14] = '\0';
	while (i < 6)
	{
		values.chr = *(temp + 5 - i);
		str[2 + (i * 2)] = ft_itochr(values.ma.e);
		str[3 + (i * 2)] = ft_itochr(values.ma.m);
		i++;
	}
	if (str[2] == '0')
		str[3] = '\0';
	temp = ft_strdup(str);
	return (temp);
}

int main(void)
{
	long double t = 20;
	long double  *n;
	char *str = "00000000000000000000000000000000000000000000000000";
	char *chr;
	unsigned char c;

	printf("\n\n%d\n\n", c);

	c = 0;
	n = &t;
	chr = (char *)(&c);

	//chr = NULL;
	//n = NULL;



str = ft_print_pointer(n);
	printf("%s\n", str);
	printf("%p\n", n);
	//printf("%s%s%s%s%s%s%hhn\n", str, str, str, str, str, str, chr);

	//printf("%hhd\n", *chr);
	//printf("%hhd\n", *chr);

	ft_putstr(ft_bytes_to_bits((char *)(&(n)), sizeof(n), "__"));




	return (0);
}
