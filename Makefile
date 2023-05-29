
NAME = minishell

SRC = main.c parsing.c ft_lexer.c errors.c check_for_arg_dollar.c\
		echo.c cd.c runcmd.c gatekeeper.c fds_and_pipes.c gatekeeper_utils.c\
		open_envs.c system_commands.c env.c export.c signal.c pwd.c exit.c\
		setenv.c system_commands_utils.c utils.c check_for_arg_dollar_utils.c\
		check_value_for_dollar.c unset_env.c setenv_utils.c heredoc.c\
		heredoc_utils1.c heredoc_utils2.c heredoc_utils3.c 

OBJ = main.o parsing.o ft_lexer.o errors.o check_for_arg_dollar.o\
		echo.o cd.o runcmd.o gatekeeper.o fds_and_pipes.o gatekeeper_utils.o\
		open_envs.o system_commands.o env.o export.o signal.o pwd.o exit.o\
		setenv.o system_commands_utils.o utils.o check_for_arg_dollar_utils.o\
		check_value_for_dollar.o unset_env.o setenv_utils.o heredoc.o\
		heredoc_utils1.o heredoc_utils2.o heredoc_utils3.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	cc $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	cc $(FLAGS) $(OBJ) -L./libft -lft -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all
