#include "minishell.h"

    void ft_export(t_list *current)
    {
        int i;

        i = 0;
        if (current->argc == 0)
        {
            while(envcpy[i] && current->argc == 0 && envcpy[i+1] != NULL)
            {
                printf("declare -x %s\n", envcpy[i]);
                i++;
            }
            return ;
        }
        while(current->argc > i)
        {
            ft_setenv(current->args[i]);
            i++;
        }
    }   
    //now work please