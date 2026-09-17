# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/10 16:41:02 by johiew            #+#    #+#              #
#    Updated: 2026/08/27 15:28:39 by thdexmun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	push_swap

NAME_BONUS	=	checker

FILES		=	disorder/disorder\
				operations/push_operations			operations/swap_operations\
				operations/rotate_operations		operations/rrotate_operations\
				main/main_utils						main/main_utils2\
				main/main_utils3					main/main_utils4\
				benchmark/benchmark\
				algorithm/bucket_sort\
				algorithm/insertion_alt\
				algorithm/radix_binary\
				algorithm/rank\
				algorithm/insert_smart_descending\
				algorithm/insert_smart_ascending\
				algorithm/bucket_insertion_sort\
				algorithm/sort_five\
				algorithm/simple\
				utils/less_than						utils/sqrt\
				utils/get_stack_edge				utils/within_range\
				utils/has_within_range				utils/is_within_range\
				utils/get_target_steps

FILES_BONUS	=	getnextline/get_next_line\
				getnextline/get_next_line_utils\
				checker/checker_utils				checker/checker

MAIN		=	srcs/main/main.c
MAIN_BONUS	=	srcs/main/main_bonus.c

SRC_DIR			=	srcs
SRC				=	$(FILES:%=$(SRC_DIR)/%.c)
SRC_BONUS		=	$(BONUS_FILES:%=$(SRC_DIR)/%.c)

OBJ_DIR			=	objects
OBJ				=	$(FILES:%=$(OBJ_DIR)/%.o)
OBJ_SUB			=	$(sort $(dir $(OBJ)))
OBJ_BONUS		=	$(FILES_BONUS:%=$(OBJ_DIR)/%.o)
OBJ_SUB_BONUS	=	$(sort $(dir $(OBJ_BONUS)))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

PRINTF_D		=	libftprintf
PRINTF_A		=	$(PRINTF_D)/libftprintf.a

INCLUDE			=	includes

all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_A)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(OBJ) $(LIBFT_A) $(MAIN) $(PRINTF_A) -o $(NAME)

debug: $(OBJ) $(PRINTF_A)
	$(CC) $(CFLAGS) -fsanitize=address -g -I$(INCLUDE) $(OBJ) $(LIBFT_A) $(MAIN) $(PRINTF_A) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ) $(OBJ_BONUS) $(PRINTF_A)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(OBJ) $(OBJ_BONUS) $(LIBFT_A) $(MAIN_BONUS) $(PRINTF_A) -o $(NAME_BONUS)

bonus_debug: $(OBJ) $(OBJ_BONUS) $(PRINTF_A)
	$(CC) $(CFLAGS) -fsanitize=address -g -I$(INCLUDE) $(OBJ_BONUS) $(OBJ) $(LIBFT_A) $(MAIN_BONUS) $(PRINTF_A) -o $(NAME_BONUS)

$(PRINTF_A):
	make -C $(PRINTF_D) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR) $(OBJ_SUB) $(OBJ_SUB_BONUS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(PRINTF_D) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C $(PRINTF_D) fclean

re: fclean all

re_bonus: fclean bonus

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_SUB):
	mkdir $(OBJ_SUB)

$(OBJ_SUB_BONUS):
	mkdir $(OBJ_SUB_BONUS)

.PHONY: all debug bonus bonus_debug clean fclean re re_bonus
