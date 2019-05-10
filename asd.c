/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:18:54 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/10 10:18:54 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"


#define TEST



int main(void)
{
	int t = 15;
	int len = 20;
	char *str;
	long double ld = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;
	long *ptr;
	double f;
	//ld = -0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001195999125990000000000990999;//8.00357;



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
	values.f = -0.12500;

	ft_putstr(ft_bytes_to_bits((char *)(&(values.f)), sizeof(values.f), "__"));

	char *chrr;

	//chrr = &(values.chr);
	//printf("%hhx ", *(chrr + 3));
	//printf("%hhx ", *(chrr + 2));
	// printf("%hhx ", *(chrr + 1));
	// printf("%hhx ", *chrr);

	printf("%d ", values.ma.s);
	printf("%d ", values.ma.e);
	printf("%d ", values.ma.m);

	//ft_putstr(ft_bytes_to_bits((char *)(&((values.ma.e))), 4, "__"));





	//ft_putnbr(*(a + 1));


	//t = ((*((int *)(&ld) + 2)) & 0x00007fff) - 16383;
	//printf("%d\n", t);

	return (0);
}
