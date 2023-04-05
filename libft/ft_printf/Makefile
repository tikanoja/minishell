# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 10:37:18 by ttikanoj          #+#    #+#              #
#    Updated: 2022/11/29 10:56:19 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ./ft_printf.c ft_printf_utils.c ft_printf_formats.c

OBJ = ./ft_printf.o ft_printf_utils.o ft_printf_formats.o

HEADERS = -I ./includes

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc -c $(FLAGS) $(HEADERS) $(SRC)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
