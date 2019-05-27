/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_values_to_str2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:23:43 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:23:43 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	помещает в ответ строку из числа с плавающей точкой
*/

void		ft_return_ldtoa_to_answer(t_prlst *list)
{
	if (list->answer != NULL || ft_strchr("feg", list->type) == NULL)
		return ;
	if (list->accur < 0)
		list->accur = 6;
	if (list->type == 'f')
		list->answer = ft_ldtoa_f(list->fvalue, list->accur, 0);
	if (list->type == 'e')
		list->answer = ft_ldtoa_e(list->fvalue, list->accur, 0);
	if (list->type == 'g')
		list->answer = ft_ldtoa_g(list->fvalue, list->accur);
	if (ft_strchr(list->answer, 'n'))
	{
		list->accur = -1;
		list->type = 'n';
		if ((list->answer)[0] == 'n')
		{
			list->plus = 0;
			list->space = 0;
		}
	}
}

/*
**	помещает в ответ строку из чара
*/

void		ft_return_chrtoa_to_answer(t_prlst *list)
{
	char	*str;

	if (list->type == 'c')
	{
		list->answer = ft_chrtoa((int)list->dvalue, list->spec);
		if (list->dvalue == 0)
			list->count_symb++;
		if (list->accur > 0)
			list->accur = list->accur - list->count_symb;
	}
	if (list->type == 's')
	{
		*((long *)(&str)) = list->dvalue;
		if (str == NULL)
			list->answer = ft_strdup("(null)");
		else
			list->answer = ft_wchrtoa(str, list->spec);
	}
	if (list->type == 'p')
		list->answer = ft_ptrtoa(list->dvalue);
}

/*
**	возвращает строку из чара
*/

char		*ft_chrtoa(unsigned int chr, int spec)
{
	char str[5];

	ft_bzero(str, 5);
	if (chr < 128 || spec != L)
		str[0] = chr;
	else if (chr < 2048)
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

/*
**	помещает в ответ адрес указателя
*/

char		*ft_ptrtoa(long num)
{
	char	str[18];
	int		i;
	char	chr;

	ft_bzero(str, 18);
	str[0] = '0';
	i = 0;
	while (i < 16 && num != 0)
	{
		chr = (num % 16) < 10 ? num % 16 + '0' : num % 16 - 10 + 'a';
		str[i] = chr;
		num = num >> 4;
		i++;
	}
	if (ft_strlen(str) == 1)
		i++;
	ft_strrevers(str);
	return (ft_strdup(str));
}

/*
**	помещает в ответ строку из чара
*/

char		*ft_wchrtoa(char *str, int spec)
{
	wchar_t	*ptr;
	size_t	len;
	char	*s;

	if (spec < L)
		return (ft_strdup(str));
	len = 0;
	ft_memcpy((void *)(&ptr), (void *)(&str), 8);
	str = NULL;
	while (ptr && ptr[len])
		len++;
	if (len == 0)
		return (ft_strnew(0));
	str = ft_strnew(len * 4);
	while (*ptr)
	{
		s = ft_chrtoa(*ptr, L);
		str = ft_strcat(str, s);
		free(s);
		ptr++;
	}
	return (str);
}
