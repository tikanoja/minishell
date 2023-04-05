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

# define PIPE 1
# define REDIR 2
# define EXEC 3



# define GREEN "\033[0;32m"
# define RESET "\033[0m"


typedef struct  s_exec
{
    char *exec;
    char **args;
}               t_exec;

typedef struct  s_redir
{
    //???
}               t_redir;

typedef struct  s_pipe
{
    int infd;
    int outfd;
}               t_pipe;

typedef struct  s_tree
{
    int type;
    void *data;
    struct s_tree *left;
    struct s_tree *right;
}               t_tree;

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


//main.c
int is_it_whitespace(char *prompt);


#endif