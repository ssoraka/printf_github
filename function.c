/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:02:20 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/29 16:02:21 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "/Users/ssoraka/Desktop/days/Libft/libft/libft.h"



void var(char *format, ...)
{
	//printf("%s\n", format);
	char *begin;
    va_list ap, ap1;
	//va_list ap1;
    va_start(ap, format);
	va_end (ap);
	va_copy(ap1, ap);
	ft_putnbr(ft_strlen(format));
	ft_putchar('\n');

	begin = format;
	while (format[0])
	{
	    if(ft_strncmp(format, "%d", 2) == 0)
	    {
	        int x = va_arg (ap, int);
	        //printf ("You passed decimal object with value %d\n", x);
	        //ft_putstr("You passed decimal object with value ");
	        ft_putstr(ft_itoa(x));
			//ft_putchar('\n');
			format = format + 1;
	    }
	    else if(ft_strncmp(format, "%s", 2) == 0)
	    {
	        char *p = va_arg (ap, char* );
	        //printf ("You passed c-string \"%s\"\n", p);
	        //ft_putstr("You passed c-string \"");
	        ft_putstr(p);
	        //ft_putstr("\"");
	        //ft_putchar('\n');
			format = format + 1;
	    }
	    else if(ft_strncmp(format, "%c", 2) == 0)
	    {
	        int c = va_arg (ap, int);
	        //printf ("You passed 1 char \'%c\'\n", (unsigned char)c);
	        //ft_putstr("You passed 1 char \'");
	        ft_putchar((unsigned char)c);
	        //ft_putstr("\'");
	        //ft_putchar('\n');
			format = format + 1;
	    }
		else
			ft_putchar(format[0]);
		format++;
	}
    //va_end (ap);

/*
	va_copy(ap, ap1);
	format = begin;
	while (format[0])
	{
	    if(ft_strncmp(format, "%d", 2) == 0)
	    {
	        int x = va_arg (ap, int);
	        ft_putstr(ft_itoa(x));
			format = format + 1;
	    }
	    else if(ft_strncmp(format, "%s", 2) == 0)
	    {
	        char *p = va_arg (ap, char* );
	        ft_putstr(p);
			format = format + 1;
	    }
	    else if(ft_strncmp(format, "%c", 2) == 0)
	    {
	        int c = va_arg (ap, int);
	        ft_putchar((unsigned char)c);
			format = format + 1;
	    }
		else
			ft_putchar(format[0]);
		format++;
	}
*/


}

int main(void)
{
	int t = -256;
	char *str = "123";
	char *s;
	int *t1;
	void *p;
	double f1 = 0;
	t1 = &t;
    //var("%d__%d__fdsfs %s\n\n\n\n", 255, 123, "qweewqeewq");
	/*
	printf("___%lu___\n", sizeof(wchar_t));
	printf("___%ld___", 0x7fff50760a58);
	printf("___%p___%lu\n", t1, sizeof(t1));
	printf("___%ld___", 0x10efacf8d);
	printf("___%p___%lu\n", str, sizeof(s));
	printf("___%010.3f___\n", f1);
	printf("___%020.5E___\n", f1);
	*/
	printf("___%lu___\n", sizeof(*str));
	printf("___%00+.10d___\n", t);
	printf("___%f___\n", f1);
	printf("___%010d___\n", t);
	printf("___%+10d___\n", t);
	printf("___%1.0d___\n", t);
	printf("___%0 10d___\n", t);
	printf("___% 010.10d___\n", t);

    //var("%s\n", "test string");
	//printf("%d", 10, 10);
    //var("%c\n", '&');
    return 0;
}
