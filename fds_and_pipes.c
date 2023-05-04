#include "minishell.h"

void free_redirection_out(t_list *current)
{
    t_list *next;

    next = current->next;
    free(current->value);
    free(next->value);
    free(current);
    free(next);
    current = NULL;
    next = NULL;
}

t_list    *handle_redirection_out(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
        printf("file not found / syntax error\n");
    else
    {
        fd = open(next->value, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
            printf("error opening file %s\n", next->value);
        prev->output = fd;
    }
    if (next->next)
    {
        prev->next = next->next;
        next->next->prev = prev;
    }
    else
        prev->next = NULL;
    free_redirection_out(current);
    return (prev);
}

t_list    *handle_redirection_in(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
        printf("file not found / syntax error\n"); //jos tää ni sitä cmd ei execute lainkaan!!
    else
    {
        fd = open(next->value, O_RDONLY, 0644);
        if (fd == -1)
            printf("error opening file %s\n", next->value);
        prev->input = fd;
    }
    if (next->next)
    {
        prev->next = next->next;
        next->next->prev = prev;
    }
    else
        prev->next = NULL;
    free_redirection_out(current);
    return (prev);
}

t_list    *handle_redirection_out_append(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
        printf("file not found / syntax error\n");
    else
    {
        fd = open(next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            printf("error opening file %s\n", next->value);
        prev->output = fd;
    }
    if (next->next)
    {
        prev->next = next->next;
        next->next->prev = prev;
    }
    else
        prev->next = NULL;
    free_redirection_out(current);
    return (prev);
}

t_list    *handle_pipe(t_list *current)
{
    t_list *prev;
    t_list *next;
    int pipefd[2];

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
        printf("nothing will read the pipe :(\n");
    if (pipe(pipefd) == -1)
        printf("error opening pipe\n");
    prev->output = pipefd[1];
    next->input = pipefd[0];
    prev->next = next;
    next->prev = prev;
    free(current->value);
    free(current);
    return (prev);
}

t_list  *handle_heredoc(t_list *current)
{
    char *delim;
    char *input;
    int pipefd[2];
    t_list *prev;

    prev = current->prev;
    delim = current->next->value;
    if (pipe(pipefd) == -1)
        printf("error opening heredoc pipe\n");
    while(1)
    {
        dup2(1, STDOUT_FILENO);
        input = readline(">");
        if (ft_strncmp(input, delim, ft_strlen(delim)) == 0)
            break ;
        dup2(pipefd[1], STDOUT_FILENO);
        ft_printf("%s", input);
        free(input);
    }
    printf("this should print\n");
    close(pipefd[1]);
    current->prev->input = pipefd[0];
    current->prev->next = current->next->next;
    current->next->next = current->prev;
    free(current->value);
    free(current);
    return (prev);
}

void    open_fds_and_pipes(t_list *head)
{
    t_list *current;

    current = head;
    while (current)
    {
        if (ft_strncmp(current->value, "|\0", 1) == 0) 
		    current = handle_pipe(current);
	    // else if (ft_strncmp(current->value, "<<\0", 2) == 0)
		//     current = handle_heredoc(current);
	    else if (ft_strncmp(current->value, ">>\0", 2) == 0)
		    current = handle_redirection_out_append(current);
	    else if (ft_strncmp(current->value, "<\0", 1) == 0)
		    current = handle_redirection_in(current);
	    else if (ft_strncmp(current->value, ">\0", 1) == 0)
		    current = handle_redirection_out(current);
        current = current->next;
    }
}