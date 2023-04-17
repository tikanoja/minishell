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

void malloc_env_copy(char ***envcpy, const char **envp, int rows, int i)
{
    while(envp[rows] != NULL)
        rows++;
    (*envcpy) = malloc((rows + 1) * sizeof(char *));
    if ((*envcpy) == NULL)
        exitmsg("env copy malloc failed");
    (*envcpy)[rows] = NULL;
    while(i < rows)
    {
        (*envcpy)[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
        if ((*envcpy)[i] == NULL)
        {
            i = 0;
            while((*envcpy)[i] != NULL)
            {
                free((*envcpy)[i]);
                i++;
            }
            free((*envcpy));
            exitmsg("env copy malloc failed");
        }
        (*envcpy)[i][ft_strlen(envp[i])] = '\0';
        i++;
    }
}

void get_env_copy(char ***envcpy, const char **envp)
{
    int i;
    int j;
    int rows;

    i = 0;
    j = 0;
    rows = 0;
    while(envp[rows] != NULL)
        rows++;
    malloc_env_copy(envcpy, envp, rows, i);
    while(envp[i])
    {
        (*envcpy)[i][j] = envp[i][j];
        j++;
        if (envp[i][j] == '\0')
        {
            i++;
            j = 0;
        }
    }
}

void runcmd(t_list *head)
{
    t_list *current;
    int i;
    int j;

    current = head;
    i = 1;
    j = 0;
    while (current != NULL)
    {
        printf("\nNode number %d\n", i);
        printf("value: %s\n", current->value);
        while(current->args[j] != NULL)
        {
            printf("args: %s\n", current->args[j]);
            j++;
        }
        j = 0;
        printf("in: %d, out: %d\n", current->input, current->output);
        current = current->next;
        i++;
    }
}

int main(int argc, char **argv, const char **envp)
{
    char *prompt;
    t_list *head;
    char **envcpy;

    prompt = NULL;
    head = NULL;
    envcpy = NULL;
    get_env_copy(&envcpy, envp);
    if (envcpy == NULL || argv[0] == NULL)
        write(1, "okay\n", 5);
    if (head != NULL || argc == 105)
        printf("variable 'head' set but not used [-Werror,-Wunused-but-set-variable]");
    while (1)
    {
        //shell nimen tilal printtais working directory???
        prompt = readline("\033[0;32mshelly\033[0m> ");
        add_history(prompt);
        if (check_quotes(prompt) == 1)
            continue ;
        //1. parsecmd will create a binary tree based on the prompt
        head = parsecmd(prompt, envcpy);
        runcmd(head);
        //2. runcmd(); will go thru the tree recursively & execute nodes & create child processes to do so 
        //parse_prompt(prompt, cmd);
        //cmd = ft_split_p(prompt, ' ');
        //is_it_builtin(cmd, prompt);
        //free(prompt);
    }
    return (0);
}