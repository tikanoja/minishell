#include "minishell.h"

void handle_ctrl_c(int signum __attribute__((unused)))
{
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void init_signals()
{
    struct sigaction sa_c;
    // Save original terminal settings
    //tcgetattr(STDIN_FILENO, orig_termios);
       /* ECHO off, other bits unchanged */
    sa_c.sa_handler = handle_ctrl_c;
    sigemptyset(&sa_c.sa_mask);
    sa_c.sa_flags = 0;
    sigaction(SIGINT, &sa_c, NULL);
    // Ignore SIGQUIT signal
    signal(SIGQUIT, SIG_IGN);
}

int termios_handler(int flag) //should this return status then?
{
    struct termios term;
    tcgetattr(STDOUT_FILENO, &term);
    if(flag)
        term.c_lflag &= ~ECHOCTL;
    else
        term.c_lflag |= ECHOCTL;
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
    return(0);
}

