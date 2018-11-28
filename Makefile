#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 18:12:44 by rsavchak          #+#    #+#              #
#    Updated: 2018/10/25 18:12:45 by rsavchak         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = asm
FLAGS = -Wall -Wextra -Werror
OBJECTS = $(SRC:.c=.o)
LIB = libft

SRC= main.c\
				name.c\
				op_tab.c\
				ft_comand.c\
				ft_reg.c\
				ft_label.c\
				ft_arguments.c\
				write.c\
				settings.c\
				check_label_end.c\
				free.c\
				code.c\

all: $(LIB) $(NAME)

$(NAME): $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -o $(NAME) -I libft/ -L $(LIB) -lft

$(LIB): libft.a

libft.a:
		$(MAKE) -C $(LIB)
%.o: 	%.c
		gcc -c $<
clean:
	$(MAKE) -C $(LIB)/ clean
	-rm $(OBJECTS)
fclean : clean
	$(MAKE) -C $(LIB)/ fclean
	-rm -v $(NAME)
re: fclean all