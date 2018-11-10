# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalexan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 20:18:39 by daalexan          #+#    #+#              #
#    Updated: 2017/11/21 20:18:43 by daalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

HEADERS = libft.h

SRC = ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memccpy.c \
       ft_memmove.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strlen.c \
       ft_strdup.c \
       ft_strcpy.c \
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
       ft_strjoin.c \
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
       ft_lstiter.c \
       ft_lstmap.c \
       ft_lstadd.c \
       ft_countsplitby.c \
       ft_nstrlen.c \
       ft_putnbrbase.c \
       ft_putnstr.c \
       ft_putnwstr.c \
       ft_putwchar.c \
       get_next_line.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	@echo "\033[36mMaster!\nYour libft.a is ready to work.\033[0m"

$(OBJ): %.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[36mMaster, allow me to report!\n I had destroy all this trash! (clean completed)\033[0m"

fclean: clean
	@rm -f libft.a
	@echo "\033[36mMaster, allow me to report!\nEven libft is not exeption (fclean completed)\033[0m"

re: fclean all
.PHONY: all clean fclean re
