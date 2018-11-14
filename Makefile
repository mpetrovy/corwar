# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalexan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/04 18:19:30 by daalexan          #+#    #+#              #
#    Updated: 2018/11/10 15:48:19 by daalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

HEADER = ./includes/libft/
VIRTM_HEADER = ./includes/

SRC = src

CFLAGS = -Wall -Werror -Wextra

CC = gcc

LIB_FILES = ./includes/libft/
VIRTM_FILES =  src/vmain.c \
			   src/op.c \
			   src/vmrdcor/rdcor.c \
			   src/carriage.c \
			   src/carrun.c \
			   src/parsing.c \
			   src/validation/filevalid.c \
			   src/initialization.c \
			   src/error_handler/file_err_hndl.c \
			   src/functions/ft_sti_hndl.c \
			   src/functions/ft_ld_hndl.c \
			   src/functions/ft_st_hndl.c \
			   src/functions/ft_add_hndl.c \
			   src/functions/ft_sub_hndl.c \
			   src/functions/ft_live_hndl.c \
			   src/functions/ft_and_hndl.c \
			   src/functions/ft_or_hndl.c \
			   src/functions/ft_xor_hndl.c \
			   src/functions/ft_setup_andorxor.c \
			   src/functions/ft_ldi_hndl.c \
			   src/functions/ft_zjump_hndl.c
OBJ = $(VIRTM_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB_FILES)libft.a
	@$(CC) -o $(NAME) $(OBJ) $(LIB_FILES)*.o

%.o: %.c $(VIRTM_HEADER)vm.h $(VIRTM_HEADER)op.h
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER) -I $(VIRTM_HEADER)

$(LIB_FILES)libft.a:
	@make -C $(LIB_FILES)
clean:
	@make clean -C $(LIB_FILES)
	rm -f $(OBJ)
fclean: clean
	@make fclean -C $(LIB_FILES)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

