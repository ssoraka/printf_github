/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:12:32 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:12:32 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	создает список из аргументов, вписывает тип и номер
*/

void		ft_list_push_back_type_num(t_prlst **begin_list,
			char type, int num, int spec)
{
	t_prlst		*check_list;

	if (begin_list == 0)
		return ;
	if (*begin_list == 0)
	{
		*begin_list = ft_create_elem(NULL);
		(*begin_list)->type = type;
		(*begin_list)->num = num;
		(*begin_list)->spec = spec;
		return ;
	}
	check_list = *begin_list;
	while (check_list->next)
	{
		check_list = check_list->next;
	}
	check_list->next = ft_create_elem(NULL);
	check_list = check_list->next;
	check_list->type = type;
	check_list->num = num;
	check_list->spec = spec;
}

/*
**	костыль для статического счетчика, больше так не делать...
*/

int			ft_arg_count(int n, int write)
{
	static int num;

	if (write == 1)
		num = n;
	if (num == 0)
		num++;
	return (num);
}

/*
**	присваиваем номер аргумента
*/

void		ft_get_number_of_arg(t_prlst *list)
{
	int	num;

	num = ft_arg_count(1, 0);
	if (list->star1 == STAR)
	{
		list->star1 = num;
		num++;
	}
	else if (list->star1 > 0)
		num = list->star1 + 1;
	if (list->star2 == -1)
	{
		list->star2 = num;
		num++;
	}
	else if (list->star2 > 0)
		num = list->star2 + 1;
	if (list->type && list->type != '%')
	{
		list->num = num;
		num++;
	}
	num = ft_arg_count(num, 1);
}

/*
**	возвращаем указатель на список с порядком аргументов
*/

t_prlst		*ft_return_list_of_args(t_prlst *list)
{
	t_prlst		*begin;
	int			num;

	num = 1;
	begin = NULL;
	while (list)
	{
		if (list->star1 != 0 && num == list->star1)
		{
			ft_list_push_back_type_num(&begin, '*', num, L);
			num++;
		}
		if (list->star2 != 0 && num == list->star2)
		{
			ft_list_push_back_type_num(&begin, '*', num, L);
			num++;
		}
		if (list->type && list->type != '%' && num == list->num)
		{
			ft_list_push_back_type_num(&begin, list->type, num, list->spec);
			num++;
		}
		list = list->next;
	}
	return (begin);
}
