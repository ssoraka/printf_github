/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:23:42 by ssoraka           #+#    #+#             */
/*   Updated: 2019/03/07 16:22:42 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdarg.h>
#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"

int		ft_printf(char *format, ...);

#define TEST

int main(void)
{
	char c = -1;
	int t = -10;
	//char *str = "12311";
	char *s = "123";
	int t1 = -10;
	int t2 = -10;
	long long int t3 = -10;
	void *p;
	long double f1 = 1010010.512351;
	int chr = 20000;
	char *str = "%hU\n";
	unsigned int ud = -1;
	long lu = -2;
	long long int d = -1;

	float ld = 10000000000000000000000000000000000000000000000.0;

	/*ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = -ld;*/

	//ft_strparse(str);
	//printf("___%-10.1d___\n",999);

	//list = ft_str_to_list(str);

	//print_list(list);

	//ft_putchar('\n');

	//ft_change_lists(list);


	//ft_putendl(str);
	t2 = ft_printf(str, 4294967296);
//printf("___%*d___\n", (double)1.1,t);
	t1 = printf(str, 4294967296);

	printf("%d__%d", t2, t1);
	//printf("%lo\n", t1);
	/////ft_putstr(ft_bytes_to_bits((char *)(&str), sizeof(str), "__"));

	//ft_putstr(ft_bytes_to_bits((char *)(&(t2)), sizeof(t2), "__"));
	//ft_putstr(ft_bytes_to_bits((char *)(&(t3)), sizeof(t3), "__"));


    return 0;
}
