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

//pitää varmaa olla int return error handling ja clean exit varten...
int check_quotes(char *str)
{
    int i;
    int single_quotes;
    int double_quotes;

    i = 0;
    single_quotes = 0;
    double_quotes = 0;
    while(str[i])
    {
        if (str[i] == '\'')
            single_quotes++;
        else if (str[i] == '"')
            double_quotes++;
        i++;
    }
    if (single_quotes % 2 == 1 || double_quotes % 2 == 1)
    {
        printf("unclosed quotes...\n");
        return (1);
    }
    return (0);
}

int main (void)
{
    char *prompt;
    t_tree *head;

    prompt = NULL;
    head = NULL;
    if (head != NULL)
        printf("variable 'head' set but not used [-Werror,-Wunused-but-set-variable]");
    while (1)
    {
        //shell nimen tilal printtais working directory???
        prompt = readline("\033[0;32mshelly\033[0m> ");
        add_history(prompt);
        if (check_quotes(prompt) == 1)
            continue ;
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