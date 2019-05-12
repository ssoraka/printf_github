/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:55:37 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/11 17:55:37 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void fun_square(int i)
{
    printf("square is %d\n", i * i);
}

void fun_sum(int i)
{
    printf("sum is %d\n", i + i);
}

void organizer(void (*fun) (int), int i)
{
	//fun = &fun_sum;
    (*fun)(i);
	printf("%p\n", fun);
}

int main(void)
{
    organizer(&fun_square, 3);
	//*fun_sum = fun_square;
    organizer(&fun_sum, 3);
	printf("%p\n", fun_square);
	printf("%p\n", fun_sum);
	//printf("%zu\n", sizeof(*fun_square));
    return (0);
}
