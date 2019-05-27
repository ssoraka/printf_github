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

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
NAME = libftprintf.a
HEADER = ./includes/
LIB = ./libft/
SRC1 = ./sources/
SRC = ft_apply_flags.c \
ft_apply_flags2.c \
ft_args.c \
ft_return_bits.c \
ft_color.c \
ft_flags_width_accur_specbase_type.c \
ft_flags_width_accur_specbase_type2.c \
ft_ldtoa_support.c \
ft_ldtoa.c \
ft_lists.c \
ft_long_arithmetic.c \
ft_ltoa_base.c \
ft_param_of_ld.c \
ft_printf.c \
ft_return_values_to_str.c \
ft_return_values_to_str2.c \
ft_strings.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make lib_refresh
	ar rc $(NAME) $(OBJS) $(LIB)*.o
	ranlib $(NAME)

%.o: $(SRC1)%.c
	$(CC) $(CFLAGS) $< -I $(HEADER) -I $(LIB)

lib_refresh:
	make -C $(LIB)

norm:
	norminette -R CheckForbiddenSourceHeader

clean:
	rm -rf *.o
	make -C $(LIB) fclean

fclean: clean
	@rm -rf $(NAME)

re: fclean all
