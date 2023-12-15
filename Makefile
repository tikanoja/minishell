NAME = minishell

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = srcs/libft
READLINE_LIB_DIR = ~/.brew/opt/readline/lib
READLINE_INCLUDE_DIR = ~/.brew/opt/readline/include

SRC = main.c parsing.c ft_lexer.c errors.c check_for_arg_dollar.c \
	echo.c cd.c runcmd.c gatekeeper.c fds_and_pipes.c gatekeeper_utils.c \
	open_envs.c system_commands.c env.c export.c signal.c pwd.c exit.c \
	setenv.c system_commands_utils.c utils.c check_for_arg_dollar_utils.c \
	check_value_for_dollar.c unset_env.c setenv_utils.c heredoc.c \
	heredoc_utils1.c heredoc_utils2.c heredoc_utils3.c \
	redirection_errors.c stdin_nodes.c setenv_ops.c redirection_frees.c \
	setenv_ops_utils.c signal_init.c run_minishell.c run_minishell_utils.c \
	env_cpy.c parsing_utils1.c parsing_utils2.c ft_lexer_utils1.c \
	ft_lexer_utils2.c stdin_nodes2.c errors2.c errors3.c runcmd_utils1.c \
	runcmd_utils2.c parsing_utils3.c run_minishell_utils2.c \
	fds_and_pipes_utils.c redirection_frees2.c

OBJ = $(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))

FLAGS = -Wall -Werror -Wextra
INCLUDES = -I $(SRCS_DIR) -I $(LIBFT_DIR) -I $(READLINE_INCLUDE_DIR)
LIBS = -L $(LIBFT_DIR) -lft -L $(READLINE_LIB_DIR) -lreadline

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	cc $(FLAGS) $(OBJ) $(LIBS) $(INCLUDES) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
