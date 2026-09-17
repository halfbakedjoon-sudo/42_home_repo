# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/27 09:48:26 by johiew            #+#    #+#              #
#    Updated: 2026/08/06 09:44:07 by johiew           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c ft_print_int.c ft_print_char.c ft_print_str.c \
       ft_print_ptr.c ft_print_u.c ft_print_lowerx.c ft_print_upperx.c \
	   ft_print_perc.c ft_convert.c
OBJ = $(SRCS:.c=.o)
LIBFT = libft
LIBFT_A = libft/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	cp $(LIBFT_A) $(NAME)
	ar rcs $(NAME) $(OBJ)

$(LIBFT_A):
	make -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIBFT_A)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
