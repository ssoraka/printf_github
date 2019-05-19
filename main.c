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

/*
typedef union	u_lega
{
	int			buf;
	struct		s_lega
	{
		unsigned int	a : 6;
		unsigned int	b : 6;
		unsigned int	c : 6;
		unsigned int	d : 6;
		unsigned int	e : 6;
		unsigned int	f : 8;
	//	unsigned char	g : 8;
	}			lega;
}				t_lega;


char		*ft_chrtoa1(unsigned int chr)
{
	char str[5];

	ft_bzero(str, 5);

	if (chr < 128)
		str[0] = (unsigned char)chr;

	else if (chr < 2048 )
	{
		str[0] = (unsigned char)(chr >> 6) + 0xc0;
		str[1] = (unsigned char)(chr & 0x0000003f) + 0x80;

	}
	else if (chr < 65536 && (chr < 55296 || chr > 57343))
	{
		str[0] = (unsigned char)(chr >> 12) + 0xe0;
		str[1] = (unsigned char)((chr >> 6) & 0x0000003f) + 0x80;
		str[2] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}
	else if (chr > 65535)
	{
		str[0] = (unsigned char)((chr >> 18) & 0x00000007) + 0xf0;
		str[1] = (unsigned char)((chr >> 12) & 0x0000003f) + 0x80;
		str[2] = (unsigned char)((chr >> 6) & 0x0000003f) + 0x80;
		str[3] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}

	return (ft_strdup(str));
}
*/


int main(void)
{
	char c = -127;
	int t = -10;
	//char *str = "12311";
	char *s = "123";
	int t1 = -10;
	int t2 = -10;
	long long int t3 = -10;
	void *p;
	long double f1 = 1010010.512351;
	int chr = 20000;

	char *str;
	unsigned int ud = -1;
	int lu = 3267;
	long d = (char)196;

	long double ld = 10000000000.0;//6.00000461;
	char *str1 = "авав%Lf434343\n";
	wchar_t *hello = L"最最(/ .□.)︵╰(゜Д゜)╯︵ /(.□. )";
	wchar_t *hello1 = L"最";

	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld ;
	ld = ld * ld * ld;

	//d = d + 0x0000000000000100l;
	//d = d + 0x0000000000000100l;
	//d = d & 0xffffffffffffff00l;
	//ft_strparse(str);
	//printf("\033[31m%s\n", "123456");

	//printf("___%2.43lf\n",ld);
	//ft_putstr("cfsdfsdf\033[33mfsdfsf\033[36msdfs\033[00mdf\n");
	//printf("__{red}_%2.43lf\n",ld);
	//list = ft_str_to_list(str);

	//print_list(list);

	//ft_putchar('\n');

	//ft_change_lists(list);

	//ft_putendl(str);
	/*t2 = ft_printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c% c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c% c%c%c%c%c%c%c %c%c%c%c%c% c%c%c%c%c%c%c%c% c%c%c%c%c% c%c%c%c%c%c%c%c",(char)128,(char)129,(char)130,(char)131,(char)132,(char)133,(char)134,(char)135,(char)136,(char)137,(char)138,(char)139,(char)140,(char)141,(char)142,(char)143,(char)144,(char)145,(char)146,(char)147,(char)148,(char)149,(char)150,(char)151,(char)152,(char)153,(char)154,(char)155,(char)156,(char)157,(char)158,(char)159,(char)160,(char)161,(char)162,(char)163,(char)164,(char)165,(char)166,(char)167,(char)168,(char)169,(char)170,(char)171,(char)172,(char)173,(char)174,(char)175,(char)176,(char)177,(char)178,(char)179,(char)180,(char)181,(char)182,(char)183,(char)184,(char)185,(char)186,(char)187,(char)188,(char)189,(char)190,(char)191,(char)192,(char)193,(char)194,(char)195,(char)196,(char)197,(char)198,(char)199,(char)200,(char)201,(char)202,(char)203,(char)204,(char)205,(char)206,(char)207,(char)208,(char)209,(char)210,(char)211,(char)212,(char)213,(char)214,(char)215,(char)216,(char)217,(char)218,(char)219,(char)220,(char)221,(char)222,(char)223,(char)224,(char)225,(char)226,(char)227,(char)228,(char)229,(char)230,(char)231,(char)232,(char)233,(char)234,(char)235,(char)236,(char)237,(char)238,(char)239,(char)240,(char)241,(char)242,(char)243,(char)244,(char)245,(char)246,(char)247,(char)248,(char)249,(char)250,(char)251,(char)252,(char)253,(char)254,(char)255);*/
//printf("___%*d___\n", (double)1.1,t);
	//ft_printf("{red}__1__{magenta}__2__{blue}__3__{cyan}__4__{yellow}__5__{green}__6__{blck}__7__8__{eoc}__9__\n");
	//t1 = ft_printf(">------------<%.42ls>------------<", L"(╯°Д°）╯︵ /(.□ . \)");

	t1 = ft_printf(str1, ld, 48, 50);

	t2 = printf(str1, ld, 48, 50);
	//printf("%p\n", &printf);



	printf("%d__%d", t2, t1);


/*
	ft_putstr(ft_bytes_to_bits((char *)(&(hello[0])), 4, "__"));

	union u_lega values;
	values.buf = 0x0e0c0a0f;
	char ch;
	ft_putstr(ft_bytes_to_bits((char *)(&(values.buf)), 4, "__"));

	ch = values.lega.a;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	ch = values.lega.b;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	ch = values.lega.c;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	ch = values.lega.d;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	ch = values.lega.e;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	ch = values.lega.f;
	ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
*/
	//printf("%lo\n", t1);
/*	int i;
	i = 0;
	while (hello[i])
	{
		str1 = ft_chrtoa1(hello[i]);
		ft_putstr(str1);//, ft_strlen(hello));
		i++;
	}
*/	//ft_putstr(ft_bytes_to_bits((char *)(&ch), 1, "__"));
	//ft_putstr(ft_bytes_to_bits((char *)(str1), sizeof(3), "__"));


    return (0);
}
