#include "minishell.h"

void handle_ctrl_c(int signum __attribute__((unused)))
{
    //printf("here!\n");
    write(STDERR_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_ctrl_c_child(int signum __attribute__((unused)))
{
    write(STDERR_FILENO, "\n", 1);
}

void handle_ctrl_d_child(int signum __attribute__((unused)))
{
    write(STDERR_FILENO, "\n", 1);
}

void handle_ctrl_c_heredoc(int signum __attribute__((unused)))
{
    init_signals();
    termios_handler(0);
    close(4);
    write(STDERR_FILENO, "\n", 1);
    run_minishell();
    // //exit (1);
    //write(STDERR_FILENO, "vittu\n", 6);
}


void handle_ctrl_d_heredoc(int signum __attribute__((unused)))
{
    write(STDERR_FILENO, "\n", 1);
}

void handle_ctrl_backslash_child(int signum __attribute__((unused)))
{
    write(STDERR_FILENO, "Quit: 3\n", 9);   
}

void init_signals()
{
    struct sigaction sa_c;
    sa_c.sa_handler = handle_ctrl_c;
    sigemptyset(&sa_c.sa_mask);
    sa_c.sa_flags = 0;
    sigaction(SIGINT, &sa_c, NULL);
    signal(SIGQUIT, SIG_IGN);
}

int termios_handler(int flag) //should this return status then?
{
    struct termios term;
    tcgetattr(STDOUT_FILENO, &term);
    if (flag)
        term.c_lflag &= ~ECHOCTL;
    else
        term.c_lflag |= ECHOCTL;
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
    return(0);
}

void init_child_signals()
{
    struct sigaction sa_c;
    struct sigaction sa_d;
    sa_c.sa_handler = handle_ctrl_c_child;
    sigemptyset(&sa_c.sa_mask);
    sa_c.sa_flags = 0;
    sigaction(SIGINT, &sa_c, NULL);

        /* Handle Ctrl-D (EOF) signal */
    sa_d.sa_handler = handle_ctrl_d_child;
    sigemptyset(&sa_d.sa_mask);
    sa_d.sa_flags = 0;
    sigaction(SIGQUIT, &sa_d, NULL);
    signal(SIGQUIT, handle_ctrl_backslash_child);
}

void init_heredoc_signals()
{
    struct sigaction sa_c;
    termios_handler(1);

    // Save original terminal settings
    //tcgetattr(STDIN_FILENO, orig_termios);
       /* ECHO off, other bits unchanged */
    sa_c.sa_handler = handle_ctrl_c_heredoc;
    sigemptyset(&sa_c.sa_mask);
    sa_c.sa_flags = 0;
    sigaction(SIGINT, &sa_c, NULL);
    // Ignore SIGQUIT signal
    signal(SIGQUIT, SIG_IGN);
}

