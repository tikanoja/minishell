#include "minishell.h"

int ft_echo(char *prompt)
{
    char **cmd;
    int nflag;
    int startpoint;

    nflag = 0;
    startpoint = 1;
    cmd = ft_split(prompt, ' ');
    if (ft_strncmp(cmd[1], "-n", (size_t)ft_strlen(cmd[1])) == 0)
    {
        nflag = 1;
        startpoint = 2;
    }
    free(cmd);
    cmd = ft_split_p(prompt, ' ');
    while (cmd[startpoint] != NULL)
    {
        printf("%s", cmd[startpoint]);
        if (cmd[startpoint + 1] != NULL)
            printf(" ");
        startpoint++;
    }
    if (nflag != 1)
        printf("\n");
    char *test = getenv("HOME");
    printf("\n\n%s\n\n", test);
    return (0);
}

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

int main (void)
{
    char *prompt;
    t_tree *head;
    while (1)
    {
        //shell nimen tilal printtais working directory???
        prompt = readline("\033[0;32mshelly\033[0m> ");
        add_history(prompt);
        //1. parsecmd will create a binary tree based on the prompt
        head = parsecmd(prompt);
        //2. runcmd(); will go thru the tree recursively & execute nodes & create child processes to do so 
        //parse_prompt(prompt, cmd);
        //cmd = ft_split_p(prompt, ' ');
        //is_it_builtin(cmd, prompt);
        //free(prompt);
    }
    return (0);
}