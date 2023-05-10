#include "minishell.h"

//pitää varmaa olla int return error handling ja clean exit varten...

int empty_input(char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    while (str[i])
    {
        if (is_it_whitespace(str[i]) == 1)
            i++;
        else
            break ;
    }
    if (i == len || len == 0)
    {
        free(str);
        return (1);
    }
    else
        return (0);
}

int find_next_quote(char quote, int i, char *str)
{
    i++;
    while(str[i])
    {
        if (str[i] == quote)
            return (i);
        i++;
    }
    return (-1);
}

int check_quotes(char *str)
{
    int	i;
    int ret;

	i = 0;
    ret = 0;
	while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            ret = find_next_quote(str[i], i, str);
            if (ret == -1)
            {
                write(2, "unclosed quotes\n", 16);
                return (1);
            }
            i = ret;
        }
        i++;
    }
	return (0);
}

void malloc_env_copy(char ***envcpy, const char **envp, int rows, int i)
{
    while(envp[rows] != NULL)
        rows++;
    (*envcpy) = ft_calloc((rows + 1), sizeof(char *));
    if (!envcpy)
        exitmsg("envcpy malloc fail");
    (*envcpy)[rows] = NULL;
    while(i < rows)
    {
        (*envcpy)[i] = ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
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
        printf("pipeflag: %d\n", current->pipe);
        printf("pipe pos: %d\n", current->pipe_position);
        current = current->next;
        i++;
    }
}

int main(int argc, char **argv, const char **envp)
{
    char *prompt;
    t_list *head;
    int status;

    prompt = NULL;
    head = NULL;
    status = 0;
    if (argc > 1 || argv == NULL)
        exitmsg("too many args");
    get_env_copy(&envcpy, envp);
    while (1)
    {
        init_signals();
        termios_handler(1);
        prompt = readline("\033[0;32mshelly\033[0m> ");
        if (!prompt)
        {
            printf("\033[0;32mshelly\033[0m>\033[A exit\n");
            free_env(envcpy);
            exit(0);
        }
        termios_handler(0);
        if (prompt[0] == '\0')
            continue ;
        add_history(prompt);
        if (check_quotes(prompt) == 1 || empty_input(prompt) == 1)
            continue ;
        head = parsecmd(prompt, envcpy);
        gatekeeper(head, status);
        open_fds_and_pipes(head);
        parse_system_commands(head);
        printlist(head);
        status = runcmd(head, envcpy);
        // rl_replace_line(prompt, 0);
        //rl_on_new_line();
        free(prompt);
        free_list(head);
    }
    return (0);
}