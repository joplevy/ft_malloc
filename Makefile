# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 18:51:52 by jplevy            #+#    #+#              #
#    Updated: 2018/10/05 18:12:15 by jplevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LN_NAME = libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc
CFLAG = -Wall -Werror -Wextra
SRC_PATH = ./src/
SRC_NAME = free.c \
			malloc.c \
			show_alloc_mem.c \
			mylib.c
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./dst/
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INCLUDE_FILE = ./includes/ft_malloc.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAG) $(OBJ) -shared -fPIC  -o $(NAME)
	@ln -fs $(NAME) $(LN_NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c  $(INCLUDE_FILE)
	-@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAG) -o $@ -c $<  -I./includes

link:
	@export DYLD_LIBRARY_PATH=.
	@export DYLD_INSERT_LIBRARIES=$(LN_NAME) 
	@export DYLD_FORCE_FLAT_NAMESPACE=1

clean:
	@$(RM) $(OBJ)
	@export DYLD_INSERT_LIBRARIES=""

fclean: clean
	@$(RM) $(NAME)

re: fclean all