/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:15:46 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/22 13:15:46 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum	e_spec1
{
	NOTYPE,
	H,
	L,
	HH,
	LL,
	Z,
	J,
	LF,
	SPECFCOUNT
}				t_spec;
typedef enum	e_colors
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	EOC
}				t_color;

#endif
