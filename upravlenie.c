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
#define TEST1

char		*ft_itoa_base(long num, int base)
{
	char	temp[50];
	int		znak;
	char	chr;
	unsigned long n;
	size_t	i;

	i = 0;
	znak = 1;
	n = num;
	if (base > 16 || base < 2)
		return (0);
	if (base == 10 && num < 0)
		znak = -1;
	ft_bzero(temp, 50);
	temp[i] = '0';
	while (n != 0)
	{
		chr = n % base;
		temp[i] = chr < 10 ? chr + '0' : chr + 'a' - 10;
		n = n / base;
		i++;
	}
	if (znak < 0)
		temp[i] = '-';
	ft_strrevers(temp);
	return (ft_strdup(temp));
}


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
	p->count_symb = 0;
	return(p);
}

void	ft_listdel(prs_lst **begin_list)
{
	prs_lst	*prev_list;

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
	if (!str[0])
		ft_list_push_back(&begin_list, ft_strdup(""));
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
	ft_strcpy(find, "%cCsSpDdiOouUxXfeEgGbB");
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
void		ft_get_number_of_arg(prs_lst *list);
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
	if (list->type == 'D' || list->type == 'O' || list->type == 'U')
	{
		list->type = list->type - 'A' + 'a';
		list->spec = L;
	}
	if (list->type == 'S' || list->type == 'C')
	{
		list->type = list->type - 'A' + 'a';
		list->spec = L;
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
	char	specf[8][4];

	i = 0;
	ft_strcpy(specf[0], "");
	ft_strcpy(specf[1], "h");
	ft_strcpy(specf[2], "l");
	ft_strcpy(specf[3], "hh");
	ft_strcpy(specf[4], "ll");
	ft_strcpy(specf[5], "z");
	ft_strcpy(specf[6], "j");
	ft_strcpy(specf[7], "L");
	if (!(list->temp) || !(*(list->temp)))
		return ;
	while(i < TYPESCOUNT)
	{
		if (!(ft_strcmp(specf[i], list->temp)))
		{
			if (list->spec == NOTYPE)
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
/*
	ft_listiter(list, &ft_find_flags);
	ft_listiter(list, &ft_find_type);
	ft_listiter(list, &ft_find_width);
	ft_listiter(list, &ft_find_accuracy);
	ft_listiter(list, &ft_find_spec);
	ft_listiter(list, &ft_get_number_of_arg);
*/

	ft_find_flags(list);
	ft_find_type(list);
	ft_find_width(list);
	ft_find_accuracy(list);
	ft_find_spec(list);
	ft_get_number_of_arg(list);

}

/*
**	поиск лишних символов ошибки по узлам
*/
int		ft_find_errors(prs_lst *list)
{
	char	find[100];
	size_t	i;
	int		error;

	ft_strcpy(find, "%cspdiouxfegbB");
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
void	ft_get_number_of_arg(prs_lst *list)
{
	static int num;

	if (num == 0)
		num++;
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

void	print_list3(prs_lst *list)
{
	while(list)
	{
		if (list->answer)
			printf("кол-во символов %zu \n",ft_strlen(list->answer));
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
	if(arg->type == '*' && ft_strchr("cspdiouxb",type))
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
		if (ft_args_are_not_similar(arg, list->star2, '*', L))
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
		if (ft_strchr("cspdiouxb*",l_args->type))// || (l_args->type == 'b' && l_args->spec != LF))
		{
			if (l_args->spec != LF)
				dnum = (long)va_arg (arg, long);
			else
				exit(2);
		}
		if (l_args->type == 'c' && (dnum & 0xffffffffffffff00l) == 0x00000000ffffff00l)
			dnum = dnum + 0x0000000000000100l;
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
		if (ft_strchr("fegB",l_args->type))// || (l_args->type == 'b' && l_args->spec == LF))
		{
			if(l_args->spec == LF)
				fnum = (long double)va_arg (arg, long double);
			else if(l_args->spec == L || l_args->spec == NOTYPE)
				fnum = (long double)va_arg (arg, double);
			else
				ft_putstr("error1\n");
				//exit(-1);
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
		if (ft_strchr("cspdiouxb",list->type))// || (list->type == 'b' && list->spec != LF))
			list->dvalue = ft_return_arg(ap, list->num, args);
		if (ft_strchr("fegB",list->type))// || (list->type == 'b' && list->spec == LF))
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
	//char chr = uchr;

	ft_bzero(str, 5);
	//printf("%u\n", chr);
	//chr = 196;
	//printf("%d\n", chr);
	//ft_putendl(ft_bytes_to_bits((char *)(&chr), 8, "__"));
	if (chr < 128)
		str[0] = (unsigned char)chr;
	//else if (chr > chr < 2048 && chr >= 192 )
	else if (chr < 2048 )
	{
		str[0] = (unsigned char)(chr >> 6) + 0xc0;
		str[1] = (unsigned char)(chr & 0x0000003f) + 0x80;
	//ft_putendl(ft_bytes_to_bits((char *)(&str), 2, "__"));
	//ft_putendl(str);
	}
	else if (chr > 2047 && chr < 65536 && (chr < 55296 || chr > 57343))
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
	//ft_putendl(ft_bytes_to_bits((char *)(&str), 4, "__"));

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
char	*ft_wchrtoa(char *str, int spec)
{
	wchar_t *ptr;

	if (spec < L)
		return (ft_strdup(str));

	ft_memcpy((void *)(&ptr), (void *)(&str), 8);
	str = ft_strdup(str);
	//printf("%p\n%p", str, ptr);
	while (*ptr)
	{
		str = ft_strjoin_free(str, ft_chrtoa(*ptr), 1, 1);
		ptr++;
	}
	return (str);
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
	{
		list->answer = ft_chrtoa((int)list->dvalue);
		if (list->dvalue == 0)
			list->count_symb++;
		if (list->accur > 0)
			list->accur = list->accur - list->count_symb;
		if (list->width > 0)
			list->width = list->width - list->count_symb;
	}
	if (list->type == 's')
	{
		*((long *)(&str)) = list->dvalue;
		if (str == NULL)
			list->answer = ft_strdup("(null)");
		else
			list->answer = ft_wchrtoa(str, list->spec);//ft_strdup(str);
	}
	if (list->type == 'p')
		list->answer = ft_ptrtoa(list->dvalue);
}




/*
**	помещает в ответ строку из числа
*/
void		ft_return_ltoa_to_answer(prs_lst *list)
{
	if (list->answer != NULL || ft_strchr("diu",list->type) == NULL)
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
	if (list->answer != NULL || ft_strchr("feg",list->type) == NULL)
		return ;
	if (list->spec != NOTYPE && list->spec != L && list->spec != LF)
		exit(-1);
		////////ft_putstr("error\n");// exit(-1)
	if (list->accur < 0)
		list->accur = 6; //стандартное округление до 6-и знаков
	if (list->type == 'f')
		list->answer = ft_ldtoa_final(list->fvalue, list->accur, 0);
	if (list->type == 'e')
		list->answer = ft_ldtoa_final_e1(list->fvalue, list->accur, 0);
	if (list->type == 'g')
		list->answer = ft_ldtoa_final_g(list->fvalue, list->accur);
	if (ft_strchr(list->answer,'n'))
	{
		list->accur = -1;
		list->type = 's';
	}
}


/*
**	помещает в ответ строку из числа в 8-иричной или 16-ричной форме
*/
void		ft_return_oxtoa_to_answer(prs_lst *list)
{
	int		base;

	base = 8;
	if (list->answer != NULL || ft_strchr("ox",list->type) == NULL)
		return ;
	if (list->type == 'x')
		base = 16;
	if (list->spec == NOTYPE)
		list->answer = ft_itoa_base((unsigned int)list->dvalue, base);
	else if (list->spec == H)
		list->answer = ft_itoa_base((unsigned short)list->dvalue, base);
	else if (list->spec == HH)
		list->answer = ft_itoa_base((unsigned char)list->dvalue, base);
	else
		list->answer = ft_itoa_base(list->dvalue, base);
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
char	*ft_num_get_cage(char *str, int cage, char type, int accur)
{
	if (cage == 0 || !str || !(ft_strcmp(str, "0")))
		return(str);
	if (type == 'o')
		if (str[0] != '0')
			return(ft_strjoin_free("0", str, 0, 1));
	if (type == 'x' || type == 'p')
	{
		if (str[0] == '0' && str[1] == '0' && accur < 0)
			str[1] = 'x';
		else if (str[0] == '0' && str[1] != '0' && accur < 0)
		{
			str[0] = 'x';
			return(ft_strjoin_free("0", str, 0, 1));
		}
		else //if (str[0] != '0')
			return(ft_strjoin_free("0x", str, 0, 1));
	}
	if (ft_strchr("feg", type) != NULL && ft_strchr(str, '.') == NULL)
		return(ft_strjoin_free(str, ".", 1, 0));
	return(str);
}


/*
**	добавляет кучу нулей слева от числа в зависимости от флага "0"
*/
char	*ft_num_stretch_zero(char *str, int width, int zero, int accur)
{
	int		len;
	char	*zeros;
	char	znak;

	znak = '0';
	if (!ft_strcmp(str, "0") && accur == 1 && width == 0)
		str[0] = '\0';
	len = ft_strlen(str);
	//if (str[0] && !ft_isdigit(str[0]) && accur == 1)
	if (str[0] && (str[0] == '-' || str[0] == '+' || str[0] == ' ') && accur == 1)
		len--;
	//printf("%d__%d\n", len, width);
	if (width <= len || zero == 0)
		return (str);
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
	{
		znak = str[0];
		str[0] = '0';
	}
	width = width - len;
	zeros = ft_strnew(width);
	ft_memset((void *)zeros, '0', width);
	zeros[0] = znak;
	//printf("%s\n", str);
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
		//printf("%zu\n", ft_strlen(list->answer));
		answer = ft_strjoin_free(answer, list->answer, 1, 1);
		list->answer = NULL;
		list = list->next;
	}
	return (answer);
}


/*
**	собираем все строки ответов
*/
int		ft_put_answer(prs_lst *list)
{
	int		count;

	count = 0;
	while (list != NULL)
	{
		list->count_symb = list->count_symb + ft_strlen(list->answer);
		//printf("%d\n", list->count_symb);
		write(1, list->answer, list->count_symb);
		free(list->answer);
		list->answer = NULL;
		count = count + list->count_symb;
		list = list->next;
	}
	return (count);
}


/*
**	укорачиваем строку по точности
*/
char	*ft_cut_str(char *str, int accur, int type)
{
	int len;

	if (ft_strchr("di", type) && !ft_strcmp(str, "0") && accur == 0)
		str[0] = '\0';
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
	if (ft_strchr("cspoxubB%",list->type) != NULL)
		list->plus = 0;
	if (ft_strchr("spcbB",list->type) != NULL)
		list->zero = 0;
	if (ft_strchr("cspoxubB%",list->type) != NULL)
		list->space = 0;
	if (ft_strchr("cspdiuebB",list->type) != NULL)
		list->cage = 0;
	if (list->type == 'x' && ft_strcmp(list->answer, "0") == 0)
		list->cage = 0;
	if (ft_strchr("diuox",list->type) != NULL && list->accur >= 0)
	{
		list->zero = 0;
	}
	if (list->plus == 1)
		list->space = 0;
	if (list->minus == 1)
		list->zero = 0;
}

/*
**	помещает в ответ строку из числа в 8-иричной или 16-ричной форме
*/
char	*ft_strupcase(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] + 'A' - 'a';
		i++;
	}
	return (str);
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

	list->answer = ft_cut_str(list->answer, list->accur, list->type);
	list->answer = ft_num_get_znak(list->answer, list->plus);
	//ft_putstr(list->answer);
	//ft_putstr("\n");


	list->answer = ft_num_get_space(list->answer, list->space);

	list->answer = ft_num_stretch_zero(list->answer, list->width, list->zero, 0);
	if (ft_strchr("diuox",list->type) != NULL)
		list->answer = ft_num_stretch_zero(list->answer, list->accur, 1, 1);

	list->answer = ft_num_get_cage(list->answer, list->cage, list->type, list->accur);

	list->answer = ft_num_stretch_spaces(list->answer, list->width, list->minus);

	if (list->captls == 1)
		list->answer = ft_strupcase(list->answer);
	//ft_putstr(str);
	//ft_putstr("\n");

}


/*
**	ищем и заменяем цвет
*/

void	ft_replace(char *str, char *repls, int num)
{
	char	color[10];
	size_t	i;
	size_t	len;

	ft_strcpy(color, "\033[00m");
	if (num < EOC)
	{
		color[2] = '3';
		color[3] = color[3] + num ;
	}
	len = ft_strlen(repls);
	ft_memmove(str + 5, str + len, ft_strlen(str + len) + 1);
	ft_memcpy(str, color, 5);
}


/*
**	ищем и заменяем цвет
*/

void	ft_give_color(prs_lst *list)
{
	char	color[9][20];
	int		i;
	char	*str;

	if (list->type != 0 || !(list->answer))
		return ;
	if (!(ft_strchr(list->answer, '{')) || !(ft_strchr(list->answer, '}')))
		return ;
	i = 0;
	ft_strcpy(color[0], "{black}");
	ft_strcpy(color[1], "{red}");
	ft_strcpy(color[2], "{green}");
	ft_strcpy(color[3], "{yellow}");
	ft_strcpy(color[4], "{blue}");
	ft_strcpy(color[5], "{magenta}");
	ft_strcpy(color[6], "{cyan}");
	ft_strcpy(color[7], "{white}");
	ft_strcpy(color[8], "{eoc}");
	while (i < 9)
	{
		if ((str = ft_strstr(list->answer, color[i])) != NULL)
			ft_replace(str, color[i], i);
		i++;
	}
}

/*
**	возвращает количество байт в зависимости от спецификатора
*/
int		ft_size_from_spec(int spec, int ldfloat)
{
	int		size;

	if (spec == LF && ldfloat == 1)
		size = 16;
	else if (spec == H && ldfloat == 0)
		size = 2;
	else if (spec == HH && ldfloat == 0)
		size = 1;
	else if (spec == NOTYPE)
		size = 4;
	else
		size = 8;
	return (size);
}

/*
**	укорачиваем строку по точности
*/
void	ft_return_btoa_to_answer(prs_lst *list)
{
	int		size;
	char	*ptr;
	float	f;
	double	d;

	f = (float)(list->fvalue);
	d = (double)(list->fvalue);
	if (list->type != 'b' && list->type != 'B')
		return ;
	if (list->type == 'B')
		size = ft_size_from_spec(list->spec, 1);
	else
		size = ft_size_from_spec(list->spec, 0);
	if (list->type == 'b')
		ptr = (char *)(&(list->dvalue));
	else if (list->type == 'B' && list->spec == LF)
		ptr = (char *)(&(list->fvalue));
	else if (list->type == 'B' && list->spec == L)
		ptr = (char *)(&d);
	else
		ptr = (char *)(&f);
	list->answer = ft_bytes_to_bits(ptr, size, "  ");
	list->answer[ft_strlen(list->answer) - 1] = '\0';
}


/*
**	формируем строки для печати у всех элементов списка
*/

void	ft_create_answers(prs_lst *list)
{
	ft_return_btoa_to_answer(list); //числа переводим в двоичный код

	ft_return_ltoa_to_answer(list); //числа переводим в строку

	ft_return_chrtoa_to_answer(list); //чары переводим в строку
	ft_return_oxtoa_to_answer(list); //чары переводим в строку
	ft_return_ldtoa_to_answer(list); //числа c точкой переводим в строку
	ft_change_flags(list); //корректировка флагов

	ft_apply_flags_to_answer(list);

	ft_give_color(list);
}



int		ft_printf(char *format, ...)
{
    va_list ap;
	prs_lst	*list;

	list = ft_str_to_list(format);
	//print_list(list);

//return(0);
	//exit(0);
	//ft_change_lists(list);
	ft_listiter(list, &ft_change_lists);
	if (ft_find_errors(list))
		exit(-1);
	//print_list(list);
	va_start(ap, format);

	/*узнаем последовательность аргументов*/
	prs_lst	*args;

	args = ft_return_list_of_args(list);

	#ifdef TEST
	//print_list(args);
	#endif

	//print_list(args);
	if (args != NULL && ft_lists_are_different(list, args))
		exit(3);
		/////ft_putstr("errors\n");
	//print_list(args);
	//printf("%p\n", args);

	ft_get_stars(ap, list, args); //возвращаем длины и точности по номерам аргументов
	va_end (ap);
	//////print_list1(list);
	//print_list2(list);

	//ft_create_answers(list);
	ft_listiter(list, &ft_create_answers);
	#ifdef TEST
	print_list3(list);
	#endif

	char	*str;
	size_t	len;
	//str = ft_get_answer(list); //собираем все ответы и в 1 и печатаем их
	//ft_putstr(str);
	//len = ft_strlen(str);
	len = ft_put_answer(list);
	ft_listdel(&list);
	ft_listdel(&args);
	//print_list(list);
	return (len);
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
