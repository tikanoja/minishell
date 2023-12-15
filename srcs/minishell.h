/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:41:28 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/31 10:58:22 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef struct s_list
{
	char			*value;
	char			**args;
	int				argc;
	int				input;
	int				output;
	int				append;
	int				system_command;
	struct s_list	*next;
	struct s_list	*prev;
	int				pipe;
	int				index;
	int				execflag;
}	t_list;

char	**g_envcpy;

//exit.c
int		ft_exit(t_list *exit_arg, int pid);
int		check_for_non_numeric(char *str);

//signals.c
void	init_signals(void);
void	handle_ctrl_c(int signum);
void	rl_replace_line(const char *text, int clear_undo);
int		termios_handler(int flag);
void	init_child_signals(void);
void	handle_ctrl_c_child(int signum __attribute__((unused)));
void	handle_ctrl_d_child(int signum __attribute__((unused)));
void	handle_ctrl_backslash_child(int signum __attribute__((unused)));

//setenv.c
int		ft_setenv(const char *value, t_list *current);
void	set_env_value(char **valuepair, const char *value, t_list *current);
int		set_env_found(char **valuepair, const char *value, \
t_list *current, int *found);
char	**copy_env(char **env, t_list *current);
char	**allocate_new_env(size_t size);
int		check_key_chars(char c, int flag);
int		is_valid_key(char *key);
int		do_special_env_set(const char *value, t_list *current);
int		check_if_equal_last(const char *value);
int		free_valuepair(char **valuepair);
int		setenv_error(char *value, char **valuepair);
int		do_append_env(char **valuepair, t_list *current);
void	exit_gracefully_free_valuepair(t_list *current, char **valuepair);
void	exit_free_valuepair_string(t_list *current, \
char **valuepair, char *str);
void	append_not_found(t_list *current, char *key, char **valuepair);
int		special_env_found(t_list *current, char *key, int found);
int		append_found(char *key, char **valuepair, int found, t_list *current);

//cd.c
int		ft_cd(t_list *current);
int		cd_path(char *path, t_list *current);
int		cd_back(t_list *current);
int		cd_home(t_list *current);

//export.c
int		ft_export(t_list *current);
void	print_full_valuepair(char **value_pair);
void	print_half_valuepair(char **value_pair);
int		export_print(int i, t_list *current);

//env.c
char	*ft_getenv(const char *name);
int		ft_env(t_list *current, int i);

//unset_env.c
int		ft_unsetenv(t_list *current, int k, int len, int status);

//heredoc.c
void	free_current_and_next(t_list *current);
char	*heredoc_env_open(char *input, t_list *current);
void	heredoc_loop(t_list *current, int pipefd[2], char *input, char *delim);
t_list	*handle_heredoc(t_list *current);

//heredoc_utils1.c
void	heredoc_assign_pipe(t_list *prev, int pipefd[2]);
t_list	*end_heredoc(t_list *current, t_list *prev, int pipefd[2]);
int		last_try_static_c(int flag);
void	heredoc_signal_c(int signum __attribute__((unused)));
void	write_input_to_pipe(char *input, int pipefd);

//heredoc_utils2.c
void	init_heredoc_env_open(int *i, int *j, \
char **input_opened, char input_env[1024]);
char	*free_heredoc_env_open(char **input, \
char *input_opened, t_list *current);
void	heredoc_env_open_iterators(char *input, \
char *input_env, int *i, int *j);
void	connect_nodes(t_list *crnt, t_list *prev, t_list **ret, int pipefd);
void	fill_args_to_prev(t_list *current, t_list *prev, \
t_list **ret, int pipefd);

//heredoc_utils3.c
int		check_heredoc_delim(t_list *current);
int		is_it_quote(char c);
void	copy_and_move_ptrs(char *input_env, char *input, int *i, int *j);
void	wait_for_child_doc(int pipefd, int pid, t_list *current);
void	pid_failed(void);

//redirection_errors.c
int		double_redir_print(int flag, t_list *current, \
t_list *head, int *status);
void	redir_directory_check_prints(char *str, int flag);
void	redir_out_null_next(t_list *prev);
void	redir_out_double_redir(t_list *prev, t_list *next);
int		redir_directory_check(char *str, t_list *prev);

//stdin_nodes.c
void	*free_empty_stdin_input(char *input, t_list *new);
int		fill_node_split_check(char *input);
void	fill_node_from_split(t_list *new, char *input, t_list *current);
char	*parse_stdin_input(char *input);
t_list	*fill_node_from_stdin(t_list *current);
void	init_parse_stdin(int *start, int *end, int *i, char *input);

// redirection_frees.c
void	free_redir_out_frees(t_list *current, t_list *next);
void	free_redir_out_handle_nodes(int *i, \
t_list **prev, t_list **next, t_list **ret);
t_list	*free_redirection_out(t_list *current, \
t_list *prev, t_list *next);
t_list	*free_pipe(t_list *current, t_list *prev, t_list *next);
void	realloc_redirection_out(t_list *prev, t_list *current, \
t_list *next, int i);

//open_fds_and_pipes.c
int		fd_syntax_check(t_list *next, t_list *prev, t_list *current);
t_list	*handle_redirection_out(t_list *current);
t_list	*open_fds_and_pipes(t_list *head);
void	handle_fd_redir(t_list **prev, t_list **next);
void	handle_pipe_pipefd(t_list **node, int pipefd, int flag);
void	handle_failed_open(t_list **current, int fd);

//system_commands.c
void	parse_system_commands(t_list *head, int pathflag);
char	**patharr_split(int *pathflag, t_list *current);
int		if_check_for_sys_cmd(t_list *current);
int		is_it_builtin_sys(char *prompt);
void	print_error_sys_cmd(t_list *current);
void	pathflag_is_zero(t_list *current, char **patharr);

//system_command_utils.c
int		findpath(char **env);
void	convert_to_lowercase(char *str);
int		variable_assign_check(char *str);
char	*get_path(char **patharr, char *cmd);
void	move_value_to_args(t_list *current);

//gatekeeper
t_list	*gatekeeper(t_list *head, int status);
void	open_quotes(t_list *current);
int		check_if_quotes(char *str);
char	*parse_quotes(char *str, int i);

//gatekeeper utils
char	*char_join(char *string, char c, t_list *current);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strnlen(const char *s, size_t n);
char	*ft_strndup(const char *string, size_t n);
int		check_for_dollar(char *string);

//open_envs
void	check_value_for_dollar(t_list *current, int status);
int		get_env_len(char *str);
int		is_valid_env_char(char c);
int		check_dollar_end(char c);
int		check_for_quote_dollar(char *str);
char	*ft_strjoin_oe(char *s1, char *s2);
void	handle_single_quotes(char c, int *flag);

//check_for_arg_dollar and check_for_arg_dollar_utils
void	check_args_for_dollar(t_list *current, int status);
char	*process_status_value(char *new_value, int status, \
int *index, t_list *current);
char	*process_environment_variable(char *new_value, \
char *arg, int *index, t_list *current);
char	*process_quoted_string(char *new_value, char *arg, \
int *index, t_list *current);
int		flag_status(int flag);
int		handle_single_quotes_args(char c, int flag);
int		handle_flag(char arg, int flag);
int		should_proccess_var(char *arg, int i, int flag);
int		should_proccess_quote_var(char *arg, int i, int flag);
char	*process_arg(char *arg, int status, t_list *current, int len);
int		check_for_dollar_whitespace(char c1, char c2);

//parsing_utils3.c
void	init_realloc_parsecmd(char ***array, int *i);
void	free_realloc3(char *prompt, char *token, t_list *current, char **array);
void	free_realloc2(char *prompt, char *token, t_list *current, char **array);
void	free_realloc1(char *prompt, char *token, t_list *current);

//parsing_utils2.c
int		ft_strncmp_casein(const char *s1, const char *s2, size_t n);
int		is_it_builtin(char *prompt);
int		is_it_redirection(char *prompt);
int		is_it_redirection_parsing(char *prompt);
int		is_it_log_operator(char *prompt);

//parsing_utils1.c
void	init_parsecmd(t_list **node, t_list **head, int *argflag);
t_list	*get_head_node(t_list *node);
void	parse_redir(int *argflag, t_list **node, char **token, t_list **head);
void	handle_parsing_end(int *argflag, char **token, t_list **head);
void	free_token_and_prompt(char **prompt, char **token);

//parsing.c
int		ft_strncmp_casein(const char *s1, const char *s2, size_t n);
int		is_it_builtin(char *prompt);
int		is_it_redirection(char *prompt);
int		is_it_redirection_parsing(char *prompt);
int		is_it_log_operator(char *prompt);
char	*get_path(char **patharr, char *token);
t_list	*add_node(t_list *node, char *token, char **g_envcpy, t_list *head);
char	**realloc_array(t_list *node, char *token);
t_list	*get_head_node(t_list *node);
t_list	*parsecmd(char *prompt, char **g_envcpy);

//ft_lexer_utils2.c
int		check_terminator(char *str, int *len);
int		handle_quotes(char *str, char quote, int start);

//ft_lexer_utils1.c
int		is_it_whitespace(char c);
int		check_token_end(char *str);
char	get_next_quote(char quote);
void	init_handle_quotes(int *len, int *quotes, int *start);
void	found_another_quote(char *quote, char *str, int *quotes, int *len);

//ft_lexer.c
int		is_it_whitespace(char c);
int		check_token_end(char *str);
int		handle_quotes(char *last_str, char quote, int start);
char	*ft_lexer(char *str, char **g_envcpy, t_list *head);

//errors.c
void	exitmsg(char *msg);
void	free_list(t_list *head);
void	free_env(char **env);
void	free_env_and_list(char **env, t_list *head);
void	free_array(char **arr);
void	free_array_and_env(char **array, char **g_envcpy, t_list *head);
int		double_redir_check(t_list *head, int *status);
void	exit_gracefully(t_list *current);
int		is_it_redirection_no_pipe(char *prompt);
int		is_it_redirection_redir_check(char *prompt);

//builtin utils
char	*ft_strcat(char *dest, const char *src);

//echo.c
int		n_definer(char *arg);
int		ft_echo(t_list *echo);
int		one_n_checker(t_list *echo);

//pwd.d
int		ft_pwd(void);

//runcmd_utils1.c
void	cmd_not_found_update_status(t_list *current, int *status);
void	init_runcmd(t_list **current, int *status, pid_t *pid, t_list **head);
int		execflag_check(t_list **current);
int		runcmd_directory_check(int *status, t_list **current);
int		end_runcmd(t_list **current, t_list **head, int status, pid_t pid);

//runcmd_utils2.c
void	close_all_fds(t_list *current);
void	init_execute_builtin(pid_t *pid, int *forkflag, int *status);
int		slash_check(char *str);
void	fd_handling_close_fds(t_list *current);
int		directory_check(char *str);

//runcmd.c
int		runcmd(t_list *head, char **g_envcpy);
int		slash_check(char *str);

//utils.c
void	free_split(char **split);
void	print_error_sys_cmd(t_list *current);
void	free_failed_split(char **split);
void	exit_split(char **split, t_list *current);

//run_minishell.c
void	run_minishell(int status);
int		prompt_if_check(char *prompt, int *status);
int		check_if_head_ok(t_list *head);
char	*get_prompt(char *prompt);
void	init_main_signals(void);
void	add_index(t_list *head);
void	ctrl_d_main(void);
int		check_log_operators(char *prompt);
int		return_log_problem(char *str);
int		find_next_quote(char quote, int i, char *str);
int		empty_input(char *str);
int		check_if_empty_quote(char *str);
int		stnc(const char *s1, const char *s2, size_t n);
int		check_for_empty_redir(char *prompt);
int		print_redir_error(char *prompt, int i, int flag);

//main.c
int		check_quotes(char *str, int flag);
void	malloc_env_copy(char ***g_envcpy, const char **envp, int rows, int i);
void	get_env_copy(char ***g_envcpy, const char **envp);
int		main(int argc, char **argv, const char **envp);

#endif
