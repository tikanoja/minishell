
NAME = minishell

SRC = main.c ft_split_pipex.c ft_split_utils.c parsing.c ft_lexer.c errors.c\
		echo.c cd.c runcmd.c

OBJ = main.o ft_split_pipex.o ft_split_utils.o parsing.o ft_lexer.o errors.o\
		echo.o cd.o runcmd.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	cc $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	cc $(FLAGS) $(OBJ) -L./libft -lft -o $(NAME) -lreadline

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all
