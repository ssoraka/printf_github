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

typedef enum	spec1
{
	NOTYPE = 0,
	H,
	L,
	HH,
	LL,
	Z,
	J,
	LF,
	TYPESCOUNT
}				spec;

typedef enum	colors
{
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	EOC
}				color;

typedef	struct			parse_list
{
	char				*answer;
	char				*data;
	char				*temp;
	struct	parse_list	*next;
	int					num;
	int					plus;
	int					minus;
	int					cage;
	int					zero;
	int					space;
	long				width;
	long				accur;
	int					star1;
	int					star2;
	enum spec1			spec;
	char				type;
	int					count_symb;
	char				captls;
	long				dvalue;
	long double			fvalue;
}						prs_lst;
