/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:24:30 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/05 17:24:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct		param_list
{
	int				maxpow_2;
	int				minpow_2;
	int				dmaxpow_2;
	int				nminpow_2;
	unsigned long	ld_bits;
	unsigned long	mask_nat;
	unsigned long	mask_dec;
	int				pow_10;
	int				accur;
	int				znak;
	char			*answer;

}					p_list;
