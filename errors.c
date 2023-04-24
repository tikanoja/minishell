#include "minishell.h"

void exitmsg(char *msg)
{
    perror(msg);
    exit(1);
}

void free_list(t_list *head)
{
    t_list *next;
    t_list *current;

    current = head;
    while (current != NULL)
    {
        if (current->input != STDIN_FILENO)
            close(current->input);
        if (current->output != STDOUT_FILENO)
            close(current->output);
        //ja ehk free args array??? katellaa
        next = current->next;
        free(current);
        current = next;
    }
}

void free_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

// void mallocprotect(t_list *head, int stageflag)
// {
    
//     while (head)
//     {
//         if (head->value)
//         free(head->value);

//         head = head->next;
//     }
// }