#include "minishell.h"

void exitmsg(char *msg)
{
    printf("%s\n", msg);
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