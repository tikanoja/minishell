#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h> //readline, printf, strerror, perror
# include <readline/readline.h> //readline
# include <readline/history.h> //readline
# include <stdlib.h> //malloc, free, exit, getenv
# include <fcntl.h> //open
# include <unistd.h> //usleep, getcwd, access, close, fork, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <sys/wait.h> //wait, waitpid, other waits as well lol
# include <sys/time.h> //gettimeofday
# include <sys/stat.h> //stat, lstat, fstat
# include <sys/ioctl.h> //ioctl
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> //opendir, readdir, closedir
# include <termios.h> //tcsetattr
# include <curses.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>  //tgetent, tgetflag, tgetnum,  tgetstr, tgoto, tputs
# include <limits.h> //macros

# define MAX_INT 2147483647
# define MAXLINE 1024 //maximum lenght of stdin command the user can input!

# define TRUE 1
# define FALSE 0

# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef struct  s_list
{
	char			*value; //esim "echo", ">" taiii "file.txt"
	char			**args; //esim "-n" ja "terve $ARG"
	int				argc; //you already know
	int				input; //fd for input
	int				output; //fd for output
	int				append; //flag if output redirection should append to file
	int				system_command; //is it a sys cmd
	struct s_list	*next; //next node
	struct s_list	*prev; //prev node
	int				pipe;
	int				index;
	int				execflag;
}               t_list;

char **envcpy; //chang this to be g_envcpy

//exit.c
int		ft_exit(t_list *exit_arg, int pid);
int		check_for_non_numeric(char *str);

//signals.c
void	init_signals();
void	handle_ctrl_c(int signum);
void	rl_replace_line (const char *text, int clear_undo);
int		termios_handler(int flag);
void	init_child_signals();
void	init_heredoc_signals();
void	handle_ctrl_c_child(int signum __attribute__((unused)));
void	handle_ctrl_d_child(int signum __attribute__((unused)));
void	handle_ctrl_c_heredoc(int signum __attribute__((unused)));
void	handle_ctrl_d_heredoc(int signum __attribute__((unused)));

//setenv.c
int		ft_setenv(const char *value);
void	set_env_value(char **env, const char *key, const char *value);
char	**copy_env(char **env);
void	free_setenv(char **env);
char	**allocate_new_env(size_t size);
int		check_key_chars(char c, int flag);
int		is_valid_key(char *key);
int do_special_env_set(const char *value);
int check_if_equal_last(const char *value);

//cd.c
int 	ft_cd(t_list *current);

//export.c
int		ft_export(t_list *current);

//env.c
char	*ft_getenv(const char *name);
int		ft_env(t_list *current);
int		ft_unsetenv(char *key);

//open_fds_and_pipes.c
t_list	*handle_redirection_out(t_list *current);
t_list	*open_fds_and_pipes(t_list *head);

//system_commands.c
int		findpath(char **env);
void	convert_to_lowercase(char *str);
int		variable_assign_check(char *str);
void	parse_system_commands(t_list *head);

//gatekeeper
t_list	*gatekeeper(t_list *head, int status);
void	open_quotes(t_list *current);
int		check_if_quotes(char *str);
char	*parse_quotes(char *str);

//gatekeeper utils
char	*char_join(char *string, char c);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strnlen(const char *s, size_t n);
char	*ft_strndup(const char *string, size_t n);
int		check_for_dollar(char *string);

//open_envs
void	check_args_for_dollar(t_list *current, int status);
void	check_value_for_dollar(t_list *current, int status);
int		get_env_len(char *str);
int		is_valid_env_char(char c);
int		check_dollar_end(char c);
int		check_for_quote_dollar(char *str);


//ft_split_utils.c
int		wordcount_p(const char *s, char c);
int		wordlen_p(char *dup, char c, int len);
char	**createempty_p(char **arr);
int		findstring(char *str);

//ft_split_pipex.c
char	**getarray_p(char *dup, char c, int wcount);
int		fillhelper2(const char *s, size_t *i, char *c);
void	fillhelper(char *arr, int *b, size_t *i, char *c);
char	**fillarr_p(char **arr, const char *s, char c, int wcount);
char	**ft_split_p(char const *s, char c);

//parsing.c
int		ft_strncmp_casein(const char *s1, const char *s2, size_t n);
int		is_it_builtin(char *prompt);
int		is_it_redirection(char *prompt);
int		is_it_redirection_parsing(char *prompt);
int		is_it_log_operator(char *prompt);
char	*get_path(char **patharr, char *token);
int		is_it_shell_command(char *token, char **envcpy);
t_list	*add_node(t_list *node, char *token, char **envcpy, t_list *head);
t_list	*add_head_node(t_list *node, t_list **head, char **envcpy);
char	**realloc_array(t_list *node, char *token, char **envcpy, t_list *head);
t_list	*get_head_node(t_list *node);
t_list	*parsecmd(char *prompt, char **envcpy);

//ft_lexer.c
int		is_it_whitespace(char c);
int		check_token_end(char *str);
int		handle_quotes(char *last_str, char quote, int start);
char	*ft_lexer(char *str, char **envcpy, t_list *head);

//errors.c
void	exitmsg(char *msg);
void	free_list(t_list *head);
void	free_env(char **env);
void	free_env_and_list(char **env, t_list *head);
void	free_array(char **arr);
void	free_array_and_env(char **array, char **envcpy, t_list *head);
int		error_handling(t_list *head);
int		double_redir_check(t_list *head);

//builtin utils
char	*ft_strcat(char *dest, const char *src);

//echo.c
int		n_definer(char *arg);
int		ft_echo(t_list *echo);
int		one_n_checker(t_list *echo);

//pwd.d
int		ft_pwd(void);
//runcmd.c
void	redirection_check(t_list *current);
int		runcmd(t_list *head, char **envcpy);
int     slash_check(char *str);

//main.c
// int ft_echo(char *prompt);
void	printlist(t_list *head);
void	run_minishell();
int		check_quotes(char *str);
void	malloc_env_copy(char ***envcpy, const char **envp, int rows, int i);
void	get_env_copy(char ***envcpy, const char **envp);
int		main(int argc, char **argv, const char **envp);



#endif