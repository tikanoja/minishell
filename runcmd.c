#include "minishell.h"

// void    redirection_check(t_list *current)
// {
//     if (current->next != NULL && is_it_redirection(current->next->value) == 1)
// }

void    runcmd(t_list *head)
{
    t_list *current;

    current = NULL;
    current = head;
    while (current)
    {
        if (ft_strncmp_casein(current->value, "echo", 5) == 0)
            ft_echo(current);
        else if (ft_strncmp_casein(current->value, "pwd", 4) == 0)
            ft_pwd();
        else if (ft_strncmp_casein(current->value, "exit", 5) == 0)
            ft_exit(current);
        current = current->next;
    }
}