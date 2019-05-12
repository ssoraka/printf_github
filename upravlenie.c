/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upravlenie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:10:54 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/10 14:10:55 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdarg.h>
#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"

/*
принимаем строчку
пока строчка не кончилась
заносим в буфер фрагмент до 1 - ого %
если процент встретился, то вычленяем фрагмент вместе с типом
присоединяем к буфферу фрагмент, вернувшийся
ищем первый
*/


prs_lst	*ft_create_elem(char *data);
void	ft_list_push_back(prs_lst **begin_list, char *data);
prs_lst	*ft_str_to_list(char *str);
void	print_list(prs_lst *list);
int		ft_find_end_of_str(char *str);


/*
**	создание пустого элемента
*/

prs_lst	*ft_create_elem(char *data)
{
	prs_lst	*p;

	if (!(p = (prs_lst	*)ft_memalloc(sizeof(prs_lst))))
		return(NULL);
	p->next = NULL;
	p->answer = NULL;
	p->data = data;
	p->temp = data;
	p->accur = 0;
	p->plus = 0;
	p->minus = 0;
	p->cage = 0;
	p->zero = 0;
	p->space = 0;
	p->width = 0;
	p->accur = 0;
	p->width = 0;
	p->star1 = 0;
	p->star2 = 0;
	p->spec = NOTYPE;
	p->type = 0;
	p->captls = 0;
	p->num = 0;
	return(p);
}

/*
**	создание элемента в конце списка и помещение data
*/

void	ft_list_push_back(prs_lst **begin_list, char *data)
{
	prs_lst *check_list;

	check_list = *begin_list;
	if (begin_list == 0)
		return ;
	if (*begin_list == 0)
	{
		*begin_list = ft_create_elem(data);
		return ;
	}
	while (check_list->next)
	{
		check_list = check_list->next;
	}
	check_list->next = ft_create_elem(data);
}

/*
**	разбиваем строку на список листов с фрагментами строки
*/

prs_lst	*ft_str_to_list(char *str)
{
	prs_lst	*begin_list;
	int		pos;

	pos = 0;
	begin_list = NULL;
	while (str[0])
	{
		pos = ft_find_end_of_str(str);
		ft_list_push_back(&begin_list, ft_strsub(str, 0, pos));
		str = str + pos;
	}
	return(begin_list);
}


/*
**	определяем длину фрагмента текста
*/

int		ft_find_end_of_str(char *str)
{
	char	find[100];
	char	*temp;
	char	*end;
	int		i;

	//надо вставить проверку на скобочку {}  для цвета
	if ((end = ft_strchr(str, '%')) == NULL)
		return (ft_strlen(str));
	if (end > str)
		return (end - str);
	ft_strcpy(find, "%cspdiouxXfeEgG");
	str++;
	end = &(str[ft_strlen(str)]);
	i = 0;
	while (i < ft_strlen(find))
	{
		temp = ft_strchr(str, (int)(find[i]));
		if (temp != NULL && temp < end)
			end = temp;
		i++;
	}
	return (end - str + 2);
}


/*
********************************************************************
**	к каждому элементу списка применяем функцию для обработки строки
**	текстовые строки переносим
********************************************************************
*/

void		ft_find_type(prs_lst *list);
void		ft_find_flags(prs_lst *list);
void		ft_find_width(prs_lst *list);
void		ft_find_accuracy(prs_lst *list);
void		ft_find_spec(prs_lst *list);
void		ft_listiter(prs_lst *lst, void (*f)(prs_lst *elem));
void		ft_change_lists(prs_lst *list);
int			ft_find_errors(prs_lst *list);
void		ft_get_number_of_arg(prs_lst *list, int *num);
/*
**	устанавливает тип для фрагмента строки в листе
*/

void		ft_find_type(prs_lst *list)
{
	if (!(list->data) || !(ft_strchr(list->data, '%')))
		return ;
	list->type = list->data[ft_strlen(list->data) - 1];
	list->data[ft_strlen(list->data) - 1] = '\0';
}

/*
**	устанавливает флаги "+-# 0" для фрагмента строки в листе
*/
void		ft_find_flags(prs_lst *list)
{
	char *str;

	str = list->temp;
	if (!ft_strchr(str, '%'))
	{
		list->answer = str;
		list->temp = NULL;
		return ;
	}
	str++;
	while (*str == '-' || *str == '+' || *str == '#' || *str == ' ' || *str == '0')
	{
		if (*str == '-')
			list->minus = 1;
		if (*str == '+')
			list->plus = 1;
		if (*str == '#')
			list->cage = 1;
		if (*str == ' ')
			list->space = 1;
		if (*str == '0')
			list->zero = 1;
		str++;
	}
	list->temp = str;
}

/*
**	устанавливает ширину для фрагмента строки в листе
*/
void		ft_find_width(prs_lst *list)
{
	char *str;

	str = list->temp;
	if (!str || !(*str))
		return ;
	if (*str == '*')
	{
		list->star1 = -1;
		list->temp++;
		return ;
	}
	if (!ft_isdigit(*str))
		return ;
	list->width = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str == '$')
	{
		list->star1 = list->width;
		list->width = 0;
		str++;
	}
	list->temp = str;
}

/*
**	устанавливает точность для фрагмента строки в листе
*/
void		ft_find_accuracy(prs_lst *list)
{
	char *str;

	str = list->temp;
	if (!str || !(*str) || *str != '.')
		return ;
	str++;
	if (*str == '*')
	{
		list->star2 = -1;
		list->temp = str + 1;
		return ;
	}
	list->accur = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str == '$')
	{
		list->star2 = list->accur;
		list->accur = 0;
		str++;
	}
	list->temp = str;
}

/*
**	надо определить спецификатор
*/

void	ft_find_spec(prs_lst *list)
{
	int		i;

	i = 0;
	char name[6][3]= {"", "h", "l", "hh", "ll", "L"};
	if (!(list->temp) || !(*(list->temp)))
		return ;
	while(i < TYPESCOUNT)
	{
		if (!(ft_strcmp(name[i], list->temp)))
		{
			list->spec = i;
			list->temp = (list->temp) + ft_strlen(list->temp);
			break;
		}
		i++;
	}
}

/*
**	применяем функции к каждому листу
*/
void	ft_listiter(prs_lst *lst, void (*f)(prs_lst *elem))
{
	prs_lst *list;

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
**	применяем функции ко всем узлам
*/
void	ft_change_lists(prs_lst *list)
{
	int		i;

	i = 1;
	ft_listiter(list, &ft_find_flags);
	//print_list(list);
	ft_listiter(list, &ft_find_type);
	//print_list(list);
	ft_listiter(list, &ft_find_width);
	//print_list(list);
	ft_listiter(list, &ft_find_accuracy);
	//print_list(list);
	ft_listiter(list, &ft_find_spec);
	//print_list(list);
	ft_get_number_of_arg(list, &i);
	//print_list(list);
	if (ft_find_errors(list))
		ft_putstr("errors\n");
}

/*
**	поиск лишних символов ошибки по узлам
*/
int		ft_find_errors(prs_lst *list)
{
	if (list == 0)
		return (1);
	while (list != NULL)
	{
		if (list->temp && *(list->temp))
			return (1);
		list = list->next;
	}
	return (0);
}

/*
**	присваиваем номер аргумента
*/
void	ft_get_number_of_arg(prs_lst *list, int *num)
{
	while (list != NULL)
	{
		if (list->star1 == -1)
		{
			list->star1 = *num;
			(*num)++;
		}
		else if (list->star1 > 0)
			*num = list->star1 + 1;
		if (list->star2 == -1)
		{
			list->star2 = *num;
			(*num)++;
		}
		else if (list->star2 > 0)
			*num = list->star2 + 1;
		if (list->type && list->type != '%')
		{
			list->num = *num;
			(*num)++;
		}
		list = list->next;
	}
}


/*
**	печатаем содержимое строки списка
*/
void	print_list(prs_lst *list)
{
	while(list)
	{
		printf("тип %c _ шир %ld _ точн. %ld _ спец-тор %d _ арг-нт %d _ арг-нт1 %d _ арг-нт2 %d _ %s\n",
		list->type, list->width, list->accur, list->spec, list->num, list->star1, list->star2, list->data);
		list = list->next;
	}
	ft_putchar('\n');
}


void var1(va_list arg, prs_lst *list)
{
	va_list ap;
	long num;
	int i;

	while (list != NULL)
	{
		va_copy(ap, arg);
		i = 1;
		if (list->star1 > 0)
		{
			while (i <= list->star1)
			{
				num = (long)va_arg (ap, long);
				i++;
			}
			list->width = num;
			list->star1 = 0;
		}
		va_end (ap);
		va_copy(ap, arg);
		i = 1;
		if (list->star2 > 0)
		{
			while (i <= list->star2)
			{
				num = (long)va_arg (ap, long);
				i++;
			}
			list->accur = num;
			list->star2 = 0;
		}
		va_end (ap);
		list = list->next;
	}
}




void var(char *format, ...)
{
    va_list ap;
	prs_lst	*list;

	list = ft_str_to_list(format);
	print_list(list);
	ft_change_lists(list);

	va_start(ap, format);
	var1(ap, list);
	va_end (ap);

	print_list(list);

/*
	long	num = 10;
	long	num2 = 20;
	void	*ptr4;
	struct	s_ma
	{
		struct	s_ma *next;
		long int *m;
		long int *e;
	};
	struct	s_ma value;
	value.m = &num;
	value.e = &num2;
	struct	s_ma *val;
	ptr4 = (char *)(&value) + 16;
	long	num3;
	long	num4;

	ft_putendl(ft_bytes_to_bits((char *)(&value), sizeof(struct	s_ma), "__"));

	num3 = *((long *)(ptr4));
	*((long *)(&ptr4)) = (long)num3;
	num3 = *((long *)(ptr4));
	printf("%ld", num3);
*/

}

int main(void)
{
	int t = 1;
	char *str = "123%*.2$ld111%*ld11%1$.2$ld";
	//char *str = "12311";
	char *s;
	long t1;
	long int t2;
	long long int t3;
	void *p;
	long double f1 = 1010010.512351;



	//ft_strparse(str);
	//printf("___%0.30d___\n", t);
	//list = ft_str_to_list(str);

	//print_list(list);

	//ft_putchar('\n');

	//ft_change_lists(list);
	t2 = 9000000000;

	var(str, 10, 20, 30, 40, 50, 60);


	//ft_putstr(ft_bytes_to_bits((char *)(&(t2)), sizeof(t2), "__"));
	//ft_putstr(ft_bytes_to_bits((char *)(&(t3)), sizeof(t3), "__"));


    return 0;
}
