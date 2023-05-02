#include "minishell.h"

// void    redirection_check(t_list *current)
// {
//     if (current->next != NULL && is_it_redirection(current->next->value) == 1)
// }

int     assignment_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void    execute_builtin(t_list *current)
{
    if (ft_strncmp_casein(current->value, "echo", 5) == 0)
            ft_echo(current);
    else if (ft_strncmp_casein(current->value, "pwd", 4) == 0)
            ft_pwd();
    else if (ft_strncmp_casein(current->value, "exit", 5) == 0)
            ft_exit(current);
}

void    execute_system_command(t_list *current, char **envcpy)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
		exitmsg("fork fail\n");
    else if (pid == 0)
	{
        if (current->input != STDIN_FILENO)
        {
            dup2(current->input, STDIN_FILENO);
            close(current->input);
        }
        if (current->output != STDOUT_FILENO)
        {
            dup2(current->output, STDOUT_FILENO);
            close(current->output);
        }
        execve(current->value, current->args, envcpy);
        exit(0);
    }
    // else{waitpid}
    // close(current->input);
    // close(current->output);
}

void    runcmd(t_list *head, char **envcpy)
{
    t_list *current;

    current = NULL;
    current = head;
    while (current)
    {
        //onko builtin? onko env var set eli = ? jos ei niin sit sen pitäis olla sys cmd tai bullshit
        // if (is_it_builtin(current->value) == 0 && assignment_check == 0)
        //     execve hommii
        if (variable_assign_check(current->value) == 1)
            printf("how to set var ???");
        else if (is_it_builtin(current->value) > 0)
            execute_builtin(current);
        else
            execute_system_command(current, envcpy);
        current = current->next;
    }
}