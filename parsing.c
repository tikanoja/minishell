#include "minishell.h"

int is_it_builtin(char *prompt)
{
    //bash tajuu et esim eCho == echo, joku strncmp joka tajuu et CAPS == caps
    int type;
    type = -1;
    if (strncmp(*prompt, "echo", 4) == 0)
        return (1);
    else if (strncmp(*prompt, "cd", 2) == 0)
        return (1);
    else if (strncmp(*prompt, "pwd", 3) == 0)
        return (1);
    else if (strncmp(*prompt, "export", 6) == 0)
        return (1);
    else if (strncmp(*prompt, "unset", 5) == 0)
        return (1);
    else if (strncmp(*prompt, "env", 3) == 0)
        return (1);
    else if (strncmp(*prompt, "env", 3) == 0)
        return (1);
    return (type);
}

int is_it_whitespace(char *prompt)
{
    if (*prompt == 9 || *prompt == 10 || *prompt == 11 || *prompt == 12 ||\
    *prompt == 13 || *prompt == 32)
        return (1);
    else
        return (0);
}

t_tree *parsecmd(char *prompt)
{
    int i;
    int type;
    t_tree *node;

    i = 0;
    type = 0;
    node = NULL;
    while(*prompt)
    {
        node = malloc(sizeof(t_tree));
        //if fails free the bin tree (joku foreach joka luikauttaa free())
        if (node == NULL)
            exit(1);
        while(is_it_whitespace(*prompt) == 1)
            prompt++;
        if (is_it_builtin(*prompt) == 1)
            node->type = EXEC;
        
    }
    return (0);
}