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

#include <stdarg.h>
#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"



int		ft_find_close_type(char *str)
{
	char	find[100];
	char	*temp;
	char	*end;
	int		i;
	int		len;

	ft_strcpy(find, "%cspdiouxXfeEgG");
	len = ft_strlen(find);
	temp = str;
	end = &(str[len]);

//printf("%s\n", str);

	i = 0;
	while (i < len)
	{
		temp = ft_strchr(str, (int)(find[i]));
		if (temp != NULL && temp < end)
			end = temp;
		i++;
	}
	//printf("%ld\n", end - str + 1);
	return (end - str + 1);
}





char	*ft_strparse(char *str)
{
	int		i;
	int		j;
	int		pos;
	char	*ans[100];
	char	*temp;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '%')
			i++;
		//printf("%d__%s\n", i , str + i);
		ans[j] = ft_strsub(str, 0, i);
		//printf("%d__%s\n", i , ans[j]);
		j++;
		if (str[i])
		{
			pos = ft_find_close_type(str + i + 1);
			ans[j] = ft_strsub(str, i + 1, pos);
			j++;
		}
		ans[j] = NULL;
		str = str + i + pos + 1;
		i = 0;
		//printf("%d__%s\n", i , str + i);
	}

/*	while (i < len)
	{
		temp = ft_strchr(str + i, '%');
		if (temp == NULL)
		{
			ans[j] = ft_strsub(str + i, 0, ft_strlen(str + i));
			j++;
			ans[j] = NULL;
			break ;
		}
		if (temp > str + i)
		{
			ans[j] = ft_strsub(str + i, 0, ft_strlen(str + i));
			j++;
			ans[j] = NULL;
		}
		ans[j] = ft_strsub(str + i, 0, i + str - temp);
		j++;
		ans[j] = NULL;
		pos = ft_find_close_type(temp + 1);
		ans[j] = ft_strsub(temp, 0, pos);
		j++;
		ans[j] = NULL;
		i = i + pos + 1;

	}*/


	//ft_putstr("\n");
	j = 0;
	while (ans[j])
	{
		ft_putendl(ans[j]);
		j++;
	}
	return (0);
}



/*

принимаем строчку
пока строчка не кончилась
заносим в буфер фрагмент до 1 - ого %
если процент встретился, то вычленяем фрагмент вместе с типом
присоединяем к буфферу фрагмент, вернувшийся
ищем первый
*/



int main(void)
{
	int t = 1;
	char *str = "123%0.20d11";
	char *s;
	int *t1;
	void *p;
	double f1 = 10.5;
	t1 = &t;

	ft_strparse(str);
	//printf("___%10.*lg___\n", t,f1);


    return 0;
}
