#include "minishell.h"

void handle_ctrl_c(int signum __attribute__((unused)))
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// void handle_ctrl_d(int signum __attribute__((unused)))
// {
//     exit(0);
// }

void init_signals(void)
{
    struct sigaction sa_c;

    sa_c.sa_handler = handle_ctrl_c;
    sigemptyset(&sa_c.sa_mask);
    sa_c.sa_flags = 0;
    sigaction(SIGINT, &sa_c, NULL);

    // sa_d.sa_handler = handle_ctrl_d;
    // sigemptyset(&sa_d.sa_mask);
    // sa_d.sa_flags = 0;
    // sigaction(SIGTERM, &sa_d, NULL);

    signal(SIGQUIT, SIG_IGN);
}