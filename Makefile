# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 18:51:52 by jplevy            #+#    #+#              #
#    Updated: 2018/10/02 19:03:39 by jplevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftmalloc.a
CC = gcc
CFLAG = -c -Wall -Werror -Wextra
SRC_PATH = ./src/
SRC_NAME = free.c \
			malloc.c \
			show_alloc_mem.c
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./dst/
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
AR = ar rc
RLIB = ranlib
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
INCLUDE_FILE = ./includes/ft_malloc.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE_FILE)
	@$(MAKE) -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)$(LIBFT_NAME) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@$(RLIB) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	-@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAG) -o $@ -c $< -I./includes

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all