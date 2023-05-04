#include "minishell.h"

    void ft_export(t_list *current)
    {
        if (current->argc != 1)
            return ;
        ft_setenv(current->args[0]);
    }   
    