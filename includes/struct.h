/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:13:28 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/22 13:13:28 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_param_list
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
	long double		ld;
	int				znak;
	char			*answer;
}					t_plist;

typedef struct		s_prlist
{
	char			*answer;
	char			*backup;
	char			*temp;
	struct s_prlist	*next;
	int				num;
	int				plus;
	int				minus;
	int				cage;
	int				zero;
	int				space;
	int				width;
	long			accur;
	int				star1;
	int				star2;
	int				spec;
	char			type;
	int				count_symb;
	char			captls;
	long			dvalue;
	long double		fvalue;
}					t_prlst;

#endif
