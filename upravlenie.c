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

#define DEFAULT 0
#define STAR -1



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
	p->accur = -1;
	p->width = 0;
	p->star1 = DEFAULT;
	p->star2 = DEFAULT;
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
	if (list->type == 'X' || list->type == 'E' || list->type == 'G')
	{
		list->type = list->type - 'A' + 'a';
		list->captls = 1;
	}
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
		list->star1 = STAR;
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
		list->star2 = STAR;
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
	//надо бы все это соединить в 1 функцию, которая будет всю эту работу
	//совершать в каждом узле, а не спускаться по от узла к узлу каждый раз...
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
	char	find[100];
	size_t	i;
	int		error;

	ft_strcpy(find, "%cspdiouxfeg");
	if (list == 0)
		return (1);
	while (list != NULL)
	{
		if (list->temp && *(list->temp))
			return (1);
		i = 0;
		error = 1;
		while (i < ft_strlen(find) + 1)
		{
			if (list->type == find[i])
				error = 0;
			i++;
		}
		if (error)
			return (error);
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
		if (list->star1 == STAR)
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

void	print_list1(prs_lst *list)
{
	while(list)
	{
		printf("тип %c _ шир %ld _ точн. %ld _ значение ll %ld _ значение Ld %Lf\n",
		list->type, list->width, list->accur, list->dvalue, list->fvalue);
		list = list->next;
	}
	ft_putchar('\n');
}

void	print_list2(prs_lst *list)
{
	while(list)
	{
		if (list->type == 'c')
			printf("\nc = %c, ", (char)(list->dvalue));
		if (list->type == 's')
			printf("s = %s, ", (char *)(list->dvalue));
		if (list->type == 'd' &&  list->spec == NOTYPE)
			printf("d = %d, ", (int)(list->dvalue));
		if (list->type == 'u' &&  list->spec == NOTYPE)
			printf("u = %u, ", (unsigned int)(list->dvalue));
		if (list->type == 'u' &&  list->spec == L)
			printf("lu = %lu, ", (unsigned long)(list->dvalue));
		if (list->type == 'u' &&  list->spec == LL)
			printf("llu = %llu, ", (unsigned long long)(list->dvalue));
		if (list->type == 'd' &&  list->spec == L)
			printf("ld = %ld, ", (long)(list->dvalue));
		if (list->type == 'd' &&  list->spec == LL)
			printf("lld = %lld, ", (long long)(list->dvalue));
		list = list->next;
	}
	ft_putchar('\n');
}


/*
**	возвращаем указатель на список с порядком аргументов
*/
void	ft_list_push_back_type_num(prs_lst **begin_list, char type, int num)
{
	prs_lst *check_list;

	if (begin_list == 0)
		return ;
	if (*begin_list == 0)
	{
		*begin_list = ft_create_elem(NULL);
		(*begin_list)->type = type;
		(*begin_list)->num = num;
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
}

/*
**	возвращаем указатель на список с порядком аргументов
*/
prs_lst	*ft_return_list_of_args(prs_lst	*check_list)
{
	prs_lst	*begin_list;
	int		num;

	num = 1;
	begin_list = NULL;
	while (check_list)
	{
		if (check_list->star1 != 0 && num == check_list->star1)
		{
			ft_list_push_back_type_num(&begin_list, '*', num);
			num++;
		}
		if (check_list->star2 != 0 && num == check_list->star2)
		{
			ft_list_push_back_type_num(&begin_list, '*', num);
			num++;
		}
		if (check_list->type && check_list->type != '%' && num == check_list->num)
		{
			ft_list_push_back_type_num(&begin_list, check_list->type, num);
			num++;
		}
		check_list = check_list->next;
	}
	return(begin_list);
}

/*
**	проверяем соответствие двух типов данных и корректируем звездочку
*/
int		ft_args_are_not_similar(prs_lst *arg, long num, char type, char spec)
{
	if (arg == 0)
		return (1);
	if (num == 0)
		return (0);
	while (arg != NULL && num > 1)
	{
		num--;
		arg = arg->next;
	}
	if (num > 1 || !arg)
		return(1);
	if (arg->type == type)
	{
		arg->spec = spec;
		return (0);
	}
	if(arg->type == '*' && ft_strchr("cspdioux",type))
	{
		arg->type = type;
		arg->spec = spec;
		return (0);
	}
	//////////
	arg->type = 'R';
	return(1);
}


/*
**	проверяем соответствие всех типов данных двух списков
*/
int		ft_lists_are_different(prs_lst *list, prs_lst *arg)
{
	if (list == 0 || arg == 0)
		return (1);
	while (list != NULL)
	{
		if (ft_args_are_not_similar(arg, list->star1, '*', L))
			return (1);//вернуть ошибку
		if (ft_args_are_not_similar(arg, list->star1, '*', L))
			return (1);//вернуть ошибку
		if (ft_args_are_not_similar(arg, list->num, list->type, list->spec))
			return (1);//вернуть ошибку
		list = list->next;
	}
	return (0);
}



/*
**	возвращаем long аргумент под соответствующим номером
*/
long	ft_return_arg(va_list ap, int arg_numb, prs_lst *l_args)
{
	int i;
	long dnum;
	va_list arg;

	va_copy(arg, ap);
	i = 1;
	dnum = 0;
	while (i <= arg_numb)
	{
		if (ft_strchr("cspdioux*",l_args->type))
			dnum = (long)va_arg (arg, long);
		l_args = l_args->next;
		i++;
	}
	va_end (arg);
	return (dnum);
}

/*
**	возвращаем long double аргумент под соответствующим номером
*/
long double	ft_return_argf(va_list ap, int arg_numb, prs_lst *l_args)
{
	int i;
	long double fnum;
	va_list arg;

	va_copy(arg, ap);
	i = 1;
	fnum = 0;
	while (i <= arg_numb)
	{
		if (ft_strchr("feg",l_args->type))
		{
			if(l_args->spec == LF)
				fnum = (long double)va_arg (arg, long double);
			if(l_args->spec == L || l_args->spec == NOTYPE)
				fnum = (long double)va_arg (arg, double);
		}
		l_args = l_args->next;
		i++;
	}
	va_end (arg);
	return (fnum);
}

/*
**	заменяем все условные номера аргументов на их содержимое
**	с учетом типов данных
*/
void	ft_get_stars(va_list ap, prs_lst *list, prs_lst *args)
{
	int	 num;

	while (list != NULL)
	{
	//	if (list->star2 == DEFAULT && list->type != '\0' && ft_strchr("feg",list->type))
	//		list->accur = 6; //стандартное округление до 6-и знаков
		if (list->star1 > 0)
			list->width = ft_return_arg(ap, list->star1, args);
		list->star1 = 0;
		if (list->star2 > 0)
			list->accur = ft_return_arg(ap, list->star2, args);
		list->star2 = 0;
		list->dvalue = 0; //не поместилось в создании узла
		list->fvalue = 0; //воможно нужен юнион
		if (ft_strchr("cspdioux",list->type))
			list->dvalue = ft_return_arg(ap, list->num, args);
		if (ft_strchr("feg",list->type))
			list->fvalue = ft_return_argf(ap, list->num, args);
		list = list->next;
	}
	va_end (ap);
}


/*
**	возвращает строку из чара
*/
char		*ft_chrtoa(unsigned int chr)
{
	char str[5];

	ft_bzero(str, 5);
	if (chr < 128)
		str[0] = (unsigned char)chr;
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
	else
	{
		str[0] = (unsigned char)((chr >> 18) & 0x00000007) + 0xf0;
		str[1] = (unsigned char)((chr >> 12) & 0x0000003f) + 0x80;
		str[2] = (unsigned char)((chr >> 6) & 0x0000003f) + 0x80;
		str[3] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}
	return (ft_strdup(str));
}


char	*ft_ptrtoa(long num)
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
	str[i] = 'x';
	str[i + 1] = '0';
	ft_strrevers(str);
	return (ft_strdup(str));
}


/*
**	помещает в ответ строку из чара
*/
void		ft_return_chrtoa_to_answer(prs_lst *list)
{
	char *str;
	if (list->type == '%')
		list->answer = ft_chrtoa('%');
	if (list->type == 'c')
		list->answer = ft_chrtoa(list->dvalue);
	if (list->type == 's')
	{
		*((long *)(&str)) = list->dvalue;
		list->answer = ft_strdup(str);
		//ft_putstr(ft_bytes_to_bits((char *)(&str), sizeof(str), "__"));
	}
	if (list->type == 'p')
		list->answer = ft_ptrtoa(list->dvalue);
}




/*
**	помещает в ответ строку из числа
*/
void		ft_return_ltoa_to_answer(prs_lst *list)
{
	if (list->answer != NULL || ft_strchr("cspoxfeg",list->type) != NULL)
		return ;
	if (list->type == 'u')
	{
		if (list->spec == NOTYPE)
			list->answer = ft_ltoa2((unsigned int)(list->dvalue), 1);
		else if (list->spec == H)
			list->answer = ft_ltoa2((unsigned short)(list->dvalue), 1);
		else if (list->spec == HH)
			list->answer = ft_ltoa2((unsigned char)(list->dvalue), 1);
		else
			list->answer = ft_ltoa2((list->dvalue), 1);
	}
	else
	{
		if (list->spec == NOTYPE)
			list->answer = ft_ltoa2((int)(list->dvalue), 0);
		else if (list->spec == H)
			list->answer = ft_ltoa2((short)(list->dvalue), 0);
		else if (list->spec == HH)
			list->answer = ft_ltoa2((char)(list->dvalue), 0);
		else
			list->answer = ft_ltoa2((list->dvalue), 0);
	}
}

/*
**	помещает в ответ строку из числа с плавающей точкой
*/
char		*ft_ldtoa_final_e1(long double ld, int accuracy, int type_g);
char		*ft_ldtoa_final(long double ld, int accuracy, int type_g);
char		*ft_ldtoa_final_g(long double ld, int accuracy);

void		ft_return_ldtoa_to_answer(prs_lst *list)
{
	//ft_putchar(list->type);
	//ft_putstr(list->answer);
	//ft_putchar(list->type);
	//ft_putstr("1\n");
	if (list->answer != NULL || ft_strchr("feg",list->type) == NULL)
		return ;
	//ft_putstr("2\n");
	if (list->accur < 0)
		list->accur = 6; //стандартное округление до 6-и знаков
	if (list->type == 'f')
		list->answer = ft_ldtoa_final(list->fvalue, list->accur, 0);
	if (list->type == 'e')
		list->answer = ft_ldtoa_final_e1(list->fvalue, list->accur, 0);
	if (list->type == 'g')
		list->answer = ft_ldtoa_final_g(list->fvalue, list->accur);
}

/*
**	добавляет кучу пробелов слева или справа от числа в зависимости от флага "-"
*/
char	*ft_num_stretch_spaces(char *str, int width, int minus)
{
	int		len;
	char	*spaces;

	len = ft_strlen(str);
	width = width - len;
	if (width <= 0)
		return (str);
	spaces = ft_strnew(width);
	ft_memset((void *)spaces, ' ', width);
	if (minus == 1)
		return(ft_strjoin_free(str, spaces, 1, 1));
	else
		return(ft_strjoin_free(spaces, str, 1, 1));
}


/*
**	добавляет пробел в начало в зависимости от флага " "
*/
char	*ft_num_get_space(char *str, int space)
{
	int		len;

	len = ft_strlen(str);
	if (space == 0)
		return (str);
	if (!str)
		str = ft_strdup(" ");
	else if (str[0] != '-' && str[0] != '+')
		str = ft_strjoin_free(" ", str, 0, 1);
	return (str);
}

/*
**	добавляет кучу нулей слева от числа в зависимости от флага "+"
*/
char	*ft_num_get_znak(char *str, int plus)
{
	if (!str || plus == 0 || str[0] == '-')
		return(str);
	return(ft_strjoin_free("+", str, 0, 1));

}

/*
**	добавляет 0 или 0х для 8-иричной и 16-иричной сс в зависимости от флага "#"
*/
char	*ft_num_get_cage(char *str, int cage, char type)
{
	if (cage == 0 || !str)
		return(str);
	if (type == 'o')
		return(ft_strjoin_free("0", str, 0, 1));
	if (type == 'x')
		return(ft_strjoin_free("0x", str, 0, 1));
	return(str);
}


/*
**	добавляет кучу нулей слева от числа в зависимости от флага "0"
*/
char	*ft_num_stretch_zero(char *str, int width, int zero)
{
	int		len;
	char	*zeros;
	char	znak;

	len = ft_strlen(str);
	znak = '0';
	if (width <= len || zero == 0)
		return (str);
	if (ft_isdigit(str[0]) == 0 && str[0] != '%')
	{
		znak = str[0];
		str[0] = '0';
	}
	width = width - len;
	zeros = ft_strnew(width);
	ft_memset((void *)zeros, '0', width);
	zeros[0] = znak;
	return (ft_strjoin_free(zeros, str, 1, 1));
}

/*
**	собираем все строки ответов
*/
char	*ft_get_answer(prs_lst *list)
{
	char	 *answer;

	answer = NULL;
	while (list != NULL)
	{
		answer = ft_strjoin_free(answer, list->answer, 1, 1);
		list = list->next;
	}
	return (answer);
}

/*
**	укаорачиваем строку по точности
*/
char	*ft_cut_str(char *str, int accur, int type)
{
	int len;

	if (type != 's')
		return (str);
	len = ft_strlen(str);
	if (len > accur && accur >= 0)
		str[accur] = '\0';
	return (str);
}


/*
**	меняем флаги в соответствии с их иерархией
*/
void	ft_change_flags(prs_lst *list)
{
	if (list->width < 0)
	{
		list->width = -(list->width);
		list->minus = 1;
	}
	if (ft_strchr("cspox",list->type) != NULL)
	{
		list->plus = 0;
		list->zero = 0;
	}
	if (ft_strchr("cspox%",list->type) != NULL)
	{
		list->plus = 0;
		list->space = 0;
	}
	if (ft_strchr("cspdiufeg",list->type) != NULL)
		list->cage = 0;
	if (list->plus == 1)
		list->space = 0;
	if (list->minus == 1)
		list->zero = 0;
}

/*
**	применяем флаги к строке ответа
*/
void	ft_apply_flags_to_answer(prs_lst *list)
{
	//if (str == 0)
	//	return ;
	//ft_putstr(list->answer);
	//ft_putstr("\n");
	list->answer = ft_num_get_cage(list->answer, list->cage, list->type);
	list->answer = ft_num_get_znak(list->answer, list->plus);
	//ft_putstr(list->answer);
	//ft_putstr("\n");
	list->answer = ft_cut_str(list->answer, list->accur, list->type);

	list->answer = ft_num_get_space(list->answer, list->space);
	list->answer = ft_num_stretch_zero(list->answer, list->width, list->zero);
	list->answer = ft_num_stretch_spaces(list->answer, list->width, list->minus);
	//ft_putstr(str);
	//ft_putstr("\n");

}


void var(char *format, ...)
{
    va_list ap;
	prs_lst	*list;

	list = ft_str_to_list(format);
	print_list(list);
	ft_change_lists(list);

	print_list(list);
	va_start(ap, format);


	/*узнаем последовательность аргументов*/
	prs_lst	*args;

	args = ft_return_list_of_args(list);
	print_list(args);

	if (ft_lists_are_different(list, args))
		ft_putstr("errors\n");
	print_list(args);

	ft_get_stars(ap, list, args); //возвращаем длины и точности по номерам аргументов
	va_end (ap);
	print_list1(list);
	//print_list2(list);

	ft_listiter(list, &ft_return_ltoa_to_answer); //числа переводим в строку
	ft_listiter(list, &ft_return_ldtoa_to_answer); //числа c точкой переводим в строку
	ft_listiter(list, &ft_return_chrtoa_to_answer); //чары переводим в строку
	ft_listiter(list, &ft_change_flags); //корректировка флагов
	ft_listiter(list, &ft_apply_flags_to_answer);


	ft_putstr(ft_get_answer(list));
	//print_list(list);

/*
	long num;
	long double dec;
	num = (long)va_arg (ap, long);
	dec = (long double)va_arg (ap, double);

	printf("%ld___%Lf\n", num, dec);

	num = (long)va_arg (ap, long);
	dec = (long double)va_arg (ap, double);

	printf("%ld___%Lf\n", num, dec);
	num = (long)va_arg (ap, long);
	dec = (long double)va_arg (ap, double);

	printf("%ld___%Lf\n", num, dec);
	num = (long)va_arg (ap, long);
	dec = (long double)va_arg (ap, double);

	printf("%ld___%Lf\n", num, dec);
*/
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
	int t = -10;
	//char *str = "12311";
	char *s = "123";
	long t1 = -10;
	long int t2 = -10;
	long long int t3 = -10;
	void *p;
	long double f1 = 1010010.512351;
	int chr = 20000;
	char *str = "%f\n";
	unsigned int ud = -1;
	unsigned short ul = -1;
	long long int d = -1;

	float ld = -0.0;

	//ft_strparse(str);
	//printf("___%-10.1d___\n",999);

	//list = ft_str_to_list(str);

	//print_list(list);

	//ft_putchar('\n');

	//ft_change_lists(list);
	t2 = 900;

	//ft_putendl(str);
	var(str, ld);
//printf("___%*d___\n", (double)1.1,t);
	printf(str, ld);
	/////ft_putstr(ft_bytes_to_bits((char *)(&str), sizeof(str), "__"));

	//ft_putstr(ft_bytes_to_bits((char *)(&(t2)), sizeof(t2), "__"));
	//ft_putstr(ft_bytes_to_bits((char *)(&(t3)), sizeof(t3), "__"));


    return 0;
}
