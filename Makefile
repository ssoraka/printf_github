#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 12:49:25 by ssoraka           #+#    #+#              #
#    Updated: 2019/03/11 20:57:23 by ssoraka          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME1 = main
SRC = /Users/ssoraka/Desktop/days/Libft/libft/libft.a

all:
	@gcc -o $(NAME1) $(SRC) upravlenie.c ldtoa3.c
	@/Users/ssoraka/Desktop/days/Libft/help_mat/clean
	./$(NAME1)

go:
	gcc -o $(NAME2) *.c
#	.//Users/ssoraka/Desktop/days/Libft/вспомогательные\ материалы/clean1
	./$(NAME2)

norm:
	norminette -R CheckForbiddenSourceHeader

clean:
	rm -rf *.o

fclean: clean
	rm -rf *.o

re: fclean all
