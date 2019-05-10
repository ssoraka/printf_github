/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:10:51 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/09 15:10:51 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

enum ConsoleColor {
Black = 0,
Blue = 1,
Green = 2,
Cyan = 3,
Red = 4,
Magenta = 5,
Brown = 6,
LightGray = 7,
DarkGray = 8,
LightBlue = 9,
LightGreen = 10,
LightCyan = 11,
LightRed = 12,
LightMagenta = 13,
Yellow = 14,
White = 15
};

black	30	40
red	31	41
green	32	42
yellow	33	43
blue	34	44
magenta	35	45
cyan	36	46
white	37	47


#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37;46m"

int main() {
    //printf("%s00%s",    YELLOW, RESET);
    //printf("%s===3%s ", RED,    RESET);
    //printf("%s-.%s\n",  WHITE,  RESET);
	printf("\033[1;7m%s\n", "123456");
	printf("%s\033[0m\n", "123456");
	return (0);
}

/*
********* СВОЙСТВА **********
Название стиля 		| Код
------------------------|----
Сбросить все свойства 	| 0
Повышенная яркость 	| 1
Пониженная яркость 	| 2
Подчеркнутый		| 4
Нормальная яркость 	| 5
Инвертированный 	| 7
Скрытый 		| 8
********** ЦВЕТА ***********
Название цвета 	|Текст	|Фон
----------------|-------|---
Черный		| 30	| 40
Красный 	| 31	| 41
Зеленый 	| 32	| 42
Желтый		| 33 	| 43
Синий		| 34 	| 44
Маджента 	| 35	| 45
Циановый 	| 36	| 46
Белый		| 37 	| 47
----------------------------

*/