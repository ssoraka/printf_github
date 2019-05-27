/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_for_ldtoa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:34:01 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/08 15:34:01 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	собираем все параметры в кучу
*/

t_plist	*ft_create_param(int accuracy, long double ld)
{
	t_plist	*p;

	if (!(p = (t_plist	*)ft_memalloc(sizeof(t_plist))))
		exit(0);
	p->answer = NULL;
	p->minpow_2 = 0;
	p->pow_10 = 1;
	p->mask_nat = 0x0000000000000001l;
	p->mask_dec = 0x8000000000000000l;
	p->accur = accuracy;
	ft_change_param_ld(ld, p);
	p->ld = ld * p->znak;
	return (p);
}

void	ft_change_param_ld(long double ld, t_plist *p)
{
	p->maxpow_2 = ((*((int *)(&ld) + 2)) & 0x00007fff) - 16383;
	p->znak = (*((long *)(&ld) + 1) & 0x0000000000008000l) == 0 ? 1 : -1;
	p->ld_bits = *((long *)(&ld)) & 0xffffffffffffffffl;
	if (p->maxpow_2 == -16383)
	{
		p->pow_10 = 1;
		return ;
	}
	if (p->maxpow_2 == 16384)
	{
		p->answer = (p->ld_bits == p->mask_dec) ?
		ft_strdup("inf") : ft_strdup("nan");
		return ;
	}
	p->minpow_2 = p->maxpow_2 - 8 * 8 + 1;
	p->pow_10 = (p->maxpow_2 < 0) ? 0 : ((p->maxpow_2 * 10000) / 33219) + 3;
	p->nminpow_2 = p->minpow_2;
	while (p->nminpow_2 < 0)
	{
		p->nminpow_2++;
		p->mask_nat = p->mask_nat << 1;
	}
	p->mask_dec = (p->mask_nat == 0) ? p->mask_dec : p->mask_nat >> 1;
	p->dmaxpow_2 = (p->maxpow_2 > -1) ? -1 : p->maxpow_2;
}

/*
**	затычка в случае переполнения при округлении числа и
**	превышении его допустимой длины
*/

char	*ft_plug(char *str, int accuracy)
{
	int len;

	len = ft_strlen(str);
	if (str[0] == '-')
		len--;
	if (ft_strchr(str, '.'))
		return (str);
	if (len == 1)
		return (str);
	if (len <= accuracy && accuracy > 1)
		return (str);
	if (str[0] == '-')
		str[2] = '\0';
	else
		str[1] = '\0';
	str = ft_ldtoa_e_adde(str, len);
	return (str);
}
