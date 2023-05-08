#include "minishell.h"

// void    redirection_check(t_list *current)
// {
//     if (current->next != NULL && is_it_redirection(current->next->value) == 1)
// }

int     assignment_check(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
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
    else if (ft_strncmp_casein(current->value, "env", 5) == 0)
            ft_env();
    else if (ft_strncmp_casein(current->value, "unset", 6) == 0 && current->argc == 1)
            ft_unsetenv(current->args[0]);
    else if (ft_strncmp_casein(current->value, "export", 7) == 0)
            ft_export(current);
    else if (ft_strncmp_casein(current->value, "cd", 3) == 0)
            ft_cd(current);
}

void  execute_system_command(t_list *current, char **envcpy)
{
    pid_t pid;
    // int status; passaa taa waitpid jos haluu selvittaa miten se meni

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
        exit(1);
    }
    else
    {
        if (current->input != STDIN_FILENO)
            close(current->input);
        if (current->output != STDOUT_FILENO)
            close(current->output);
    }
}

int    runcmd(t_list *head, char **envcpy)
{
    t_list *current;
    pid_t pid;
    int status;
    
    int i = 0;
    current = NULL;
    current = head;
    status = 0;
    while (current)
    {
        if (current->value == NULL)
        {
            printf("shelly: %s: command not found\n", current->args[0]);
            current = current->next;
            continue;
        }
        else if (variable_assign_check(current->value) == 1)
        {   
            ft_setenv(current->value);
        }
        else if (is_it_builtin(current->value) > 0)
        {
            execute_builtin(current);
            if (current->input != STDIN_FILENO)
                close(current->input);
            if (current->output != STDOUT_FILENO)
                close(current->output);
        }
        else if (current->system_command == 1)
        {
            execute_system_command(current, envcpy);
            i++;
        }
        current = current->next;
    }
    while ((pid = waitpid(-1, &status, 0)) > 0);
    // {
    // // handle child process exit status
    //     if (WIFEXITED(status))
    //         printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    //     else if (WIFSIGNALED(status))
    //         printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
    // }
    return(status);
}