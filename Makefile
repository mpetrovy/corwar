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
FT_PRINTF = ./includes/ft_printf/

SRC = src

CFLAGS = -Wall -Werror -Wextra

CC = gcc -g

LIB_FILES = ./includes/libft/
FT_PRINTF_FILES = ./includes/ft_printf/
VIRTM_FILES =  src/vmain.c \
			   src/vmrdcor/rdcor.c \
			   src/carriage.c \
			   src/carrun.c \
			   src/parsing.c \
			   src/flag_debug.c \
			   src/move_carriage.c \
			   src/validation/filevalid.c \
			   src/initialization.c \
			   src/error_handler/file_err_hndl.c \
			   src/functions/ft_setup_andorxor.c \
			   src/functions/ft_live_hndl.c \
			   src/functions/ft_ld_hndl.c \
			   src/functions/ft_st_hndl.c \
			   src/functions/ft_add_hndl.c \
			   src/functions/ft_sub_hndl.c \
			   src/functions/ft_and_hndl.c \
			   src/functions/ft_or_hndl.c \
			   src/functions/ft_xor_hndl.c \
			   src/functions/ft_ldi_hndl.c \
			   src/functions/ft_zjump_hndl.c \
			   src/functions/ft_sti_hndl.c \
			   src/functions/ft_fork_hndl.c \
			   src/functions/ft_lld_hndl.c \
			   src/functions/ft_lldi_hndl.c \
			   src/functions/ft_lfork_hndl.c \
			   src/functions/ft_aff_hndl.c
OBJ = $(VIRTM_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB_FILES)libft.a $(FT_PRINTF_FILES)libftprintf.a
	@$(CC) -o $(NAME) $(OBJ) $(LIB_FILES)*.o $(FT_PRINTF_FILES)obj1/*.o $(FT_PRINTF_FILES)obj1/type/*.o $(FT_PRINTF_FILES)obj1/parsing/*.o $(FT_PRINTF_FILES)obj2/ft_memjoin.o

%.o: %.c $(VIRTM_HEADER)vm.h $(VIRTM_HEADER)op.h
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER) -I $(VIRTM_HEADER) -I $(FT_PRINTF)

$(FT_PRINTF_FILES)libftprintf.a:
	make -C $(FT_PRINTF)
$(LIB_FILES)libft.a:
	@make -C $(LIB_FILES)
clean:
	@make clean -C $(LIB_FILES)
	@make clean -C $(FT_PRINTF)
	rm -f $(OBJ)
fclean: clean
	@make fclean -C $(LIB_FILES)
	@make fclean -C $(FT_PRINTF)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

