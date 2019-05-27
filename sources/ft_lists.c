/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:29:38 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/21 18:29:38 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	создание пустого элемента
*/

t_prlst		*ft_create_elem(char *data)
{
	t_prlst		*p;

	if (!(p = (t_prlst	*)ft_memalloc(sizeof(t_prlst))))
		return (NULL);
	p->next = NULL;
	p->answer = NULL;
	p->temp = data;
	p->accur = 0;
	p->plus = 0;
	p->minus = 0;
	p->cage = 0;
	p->zero = 0;
	p->space = 0;
	p->width = 0;
	p->accur = -1;
	p->width = 0;
	p->star1 = DEFAULT;
	p->star2 = DEFAULT;
	p->spec = NOTYPE;
	p->type = 0;
	p->captls = 0;
	p->num = 0;
	p->count_symb = 0;
	return (p);
}

void		ft_listdel(t_prlst **begin_list)
{
	t_prlst		*prev_list;

	while (*begin_list != 0)
	{
		prev_list = *begin_list;
		*begin_list = (*begin_list)->next;
		prev_list->next = 0;
		free(prev_list);
	}
	*begin_list = NULL;
}

/*
**	создание элемента в конце списка и помещение data
*/

t_prlst		*ft_list_push_back(t_prlst **begin_list, char *data)
{
	t_prlst		*check_list;

	check_list = *begin_list;
	if (begin_list == 0)
		return (NULL);
	if (*begin_list == 0)
	{
		*begin_list = ft_create_elem(data);
		return (*begin_list);
	}
	while (check_list->next)
	{
		check_list = check_list->next;
	}
	check_list->next = ft_create_elem(data);
	return (check_list->next);
}

/*
**	применяем функции к каждому листу
*/

void		ft_listiter(t_prlst *lst, void (*f)(t_prlst *elem))
{
	t_prlst		*list;

	if (f == 0)
		return ;
	while (lst != NULL)
	{
		list = lst;
		lst = list->next;
		f(list);
	}
}

/*
**	разбиваем строку на список листов с фрагментами строки
*/

t_prlst		*ft_str_to_list(char *str)
{
	t_prlst	*begin_list;
	t_prlst *check_list;
	int		pos;

	pos = 0;
	begin_list = NULL;
	ft_arg_count(0, 1);
	if (!str || !str[0])
	{
		check_list = ft_list_push_back(&begin_list, 0);
		check_list->answer = ft_strdup("");
	}
	while (str && str[0])
	{
		check_list = ft_list_push_back(&begin_list, str);
		ft_change_lists(check_list);
		str = check_list->temp;
	}
	return (begin_list);
}
