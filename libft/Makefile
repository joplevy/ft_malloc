# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 14:21:43 by jplevy            #+#    #+#              #
#    Updated: 2017/05/30 20:08:01 by joeyplevy        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAG = -c -Wall -Werror -Wextra
SRC_NAME = ft_bzero.c \
		   ft_memccpy.c \
		   ft_memcpy.c \
		   ft_memset.c \
		   ft_memmove.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_strlen.c \
		   ft_strcpy.c \
		   ft_strdup.c \
		   ft_strncpy.c \
		   ft_strcat.c \
		   ft_strncat.c \
		   ft_strlcat.c \
		   ft_strchr.c \
		   ft_strrchr.c \
		   ft_strstr.c \
		   ft_strnstr.c \
		   ft_strcmp.c \
		   ft_strncmp.c \
		   ft_atoi.c \
		   ft_isalpha.c \
		   ft_isdigit.c \
		   ft_isalnum.c \
		   ft_isascii.c \
		   ft_isprint.c \
		   ft_toupper.c \
		   ft_tolower.c \
		   ft_memalloc.c \
		   ft_memdel.c \
		   ft_strnew.c \
		   ft_strdel.c \
		   ft_strclr.c \
		   ft_striter.c \
		   ft_striteri.c \
		   ft_strmap.c \
		   ft_strmapi.c \
		   ft_strequ.c \
		   ft_strnequ.c \
		   ft_strsub.c \
		   ft_strsub_no_leaks.c \
		   ft_strjoin.c \
		   ft_strjoin_no_leaks.c \
		   ft_strtrim.c \
		   ft_strsplit.c \
		   ft_itoa.c \
		   ft_putchar.c \
		   ft_putstr.c \
		   ft_putendl.c \
		   ft_putnbr.c \
		   ft_putchar_fd.c \
		   ft_putstr_fd.c \
		   ft_putendl_fd.c \
		   ft_putnbr_fd.c \
		   ft_lstnew.c \
		   ft_lstdelone.c \
		   ft_lstdel.c \
		   ft_lstadd.c \
		   ft_lstadd_back.c \
		   ft_lstpushback.c \
		   ft_lstiter.c \
		   ft_lstmap.c \
		   ft_power.c \
		   get_next_line.c \
		   ft_printf/ft_printf.c\
		   ft_printf/get_args.c\
		   ft_printf/ft_itoa_base.c\
		   ft_printf/ft_number.c\
		   ft_printf/flags.c \
		   ft_printf/ft_wide_char.c \
		   ft_printf/altnorme.c \
		   ft_abs.c \
		   ft_lstfree.c \
		   ft_lstdelnode.c \
		   ft_get_args.c


OBJ_NAME = $(SRC_NAME:.c=.o)
AR = ar rc
RLIB = ranlib
HDR = -I libft.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ_NAME)
	# @$(CC) $(CFLAG) $(SRC_NAME)
	@$(AR) $(NAME) $(OBJ_NAME)
	@$(RLIB) $(NAME)

%.o: %.c
	@echo $@
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo "  Well done"

clean:
	@$(RM) $(OBJ_NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
