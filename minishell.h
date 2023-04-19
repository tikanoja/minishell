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

# define MAX_INT 2147483647
# define MAXLINE 1024 //maximum lenght of stdin command the user can input!

# define TRUE 1
# define FALSE 0

# define GREEN "\033[0;32m"
# define RESET "\033[0m"

// typedef enum e_builtinCommand
// {
//     ft_echo,
//     ft_cd,
//     ft_pwd,
//     ft_export,
//     ft_unset,
//     ft_env,
//     ft_exit,
//     ft_invalid
// }       t_builtinCommand;

typedef enum e_tokenType
{
    COMMAND,
    ARGUMENT,
    PIPE,
    REDIRECTION,
    INPUT,
    OUPUT,
    APPEND,
    BACKGROUND,
    INVALID
}       t_tokenType;

typedef struct  s_list
{
    t_tokenType tokenType; //COMMAND, PIPE, REDIRECTION etc...
    // t_builtinCommand builtinCommand; //builtin commands
    char *value; //esim "echo", ">" taiii "file.txt"
    char *args[20]; //esim "-n" ja "terve $ARG"
    int argc; //you already know
    int input; //fd for input
    int output; //fd for output
    int append; //flag if output redirection should append to file
    int background; //ei oo mitää hajuu
    struct s_list *next; //next node
    struct s_list *prev; //prev node
}               t_list;

//ft_split_utils.c
int	wordcount_p(const char *s, char c);
int	wordlen_p(char *dup, char c, int len);
char	**createempty_p(char **arr);
int	findstring(char *str);

//ft_split_pipex.c
char	**getarray_p(char *dup, char c, int wcount);
int	fillhelper2(const char *s, size_t *i, char *c);
void	fillhelper(char *arr, int *b, size_t *i, char *c);
char	**fillarr_p(char **arr, const char *s, char c, int wcount);
char	**ft_split_p(char const *s, char c);

//parsing.c
int	ft_strncmp_casein(const char *s1, const char *s2, size_t n);
int is_it_builtin(char *prompt);
int is_it_redirection(char *prompt);
char	*get_path(char **patharr, char *token);
int is_it_shell_command(char *token, char **envcpy);
t_list *parsecmd(char *prompt);

//ft_lexer.c
int is_it_whitespace(char c);
char *handle_quotes(char *last_str, char quote);
char    *ft_lexer_helper(char *last_str);
char *ft_lexer(char *str);

//errors.c
void exitmsg(char *msg);
void free_list(t_list *head);

//builtin utils
char *ft_strcat(char *dest, const char *src);

//echo.c
int n_definer(char *arg);
int ft_echo(t_list *echo);
void ft_pwd();
void ft_exit(int exit_status);

//runcmd.c
void    redirection_check(t_list *current);
void    runcmd(t_list *head);

//main.c
// int ft_echo(char *prompt);
int check_quotes(char *str);
void malloc_env_copy(char ***envcpy, const char **envp, int rows, int i);
void get_env_copy(char ***envcpy, const char **envp);
int main (int argc, char **argv, const char **envp);



#endif