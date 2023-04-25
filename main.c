#include "minishell.h"

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
    if (!envcpy)
        exitmsg("envcpy malloc fail");
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

void printlist(t_list *head)
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
        printf("argc: %d\n", current->argc);
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
    if (argc > 1 || argv == NULL)
        exitmsg("too many args");
    get_env_copy(&envcpy, envp);
    while (1)
    {
        prompt = readline("\033[0;32mshelly\033[0m> ");
        if (!prompt)
        {
            free_env(envcpy);
            exitmsg("readline malloc fail");
        }
        add_history(prompt);
        if (check_quotes(prompt) == 1)
            continue ;
        head = parsecmd(prompt, envcpy);
        printlist(head);
        runcmd(head);
        free(prompt);
        free_list(head);
    }
    return (0);
}