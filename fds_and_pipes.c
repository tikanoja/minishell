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
        fd = open(next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

t_list *fill_node_from_stdin(t_list *current)
{
    t_list *new;

    new = malloc(sizeof(t_list)); //protect
    new->args = malloc(sizeof(char **)); //protect
    new->args[0] = NULL;
    new->argc = 0;
    new->pipe = 1;
    new->pipe_position = 0;
    new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
    new->prev = current;
    new->next = NULL;
    new->value = readline(">"); // ehk pitaa lisaa splitti!
    return (new);
}

t_list    *handle_pipe(t_list *current)
{
    t_list *prev;
    t_list *next;
    int pipefd[2];

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
        next = fill_node_from_stdin(current);
    if (pipe(pipefd) == -1)
        printf("error opening pipe\n");
    prev->output = pipefd[1];
    prev->pipe = 1;
    next->input = pipefd[0];
    next->pipe = 1;
    prev->next = next;
    next->prev = prev;
    free(current->value);
    free(current);
    return (prev);
}
int is_it_quote(char c)
{
    if(c == '\'' || c == '\"')
        return (1);
    else
        return (0);
}

t_list  *handle_heredoc(t_list *current)
{
    char    *delim;
    char    *input;
    int     pipefd[2];
    t_list  *prev;
    char    input_env[1024];
    char    *input_opened;
    int     i;
    int     j;
    int     flag;

    prev = current->prev;
    delim = ft_strdup(current->next->value);
    i = 0;
    j = 0;
    flag = 0;
    input_opened = malloc(1);
    if (pipe(pipefd) == -1)
        printf("error opening heredoc pipe\n");
    while(1)
    {
        flag = 0;
        i = 0;
        init_heredoc_signals();
        input = readline(">");
        if (!input)
        {
            printf("\033[1A> ");
            break;
        }
        while(input[i] && check_for_dollar(input) == 1)
        {
            flag = 1;
            if(input[i] == '$')
            {
                i++;
                while(is_it_whitespace(input[i]) == 0 && is_it_quote(input[i]) == 0 && input[i])
                {
                    input_env[j] = input[i];
                    i++;
                    j++;
                }
                input_opened = ft_strjoin(input_opened, ft_getenv(input_env));
                ft_bzero(input_env, (size_t)j);
                j = 0;
            }
            input_opened = char_join(input_opened, input[i]);
            i++;
        }
        if(flag == 1)
        {
            free(input);
            input = ft_strdup(input_opened);
            free(input_opened);
        }
        if ((ft_strncmp(input, delim, ft_strlen(delim)) == 0 && input[ft_strlen(delim)] == '\0'))
        {
            free(input);
            break ;
        }
        ft_putstr_fd(input, pipefd[1]);
        ft_putchar_fd('\n', pipefd[1]);
        free(input);
    }
    close(pipefd[1]);
    init_signals();
    free(delim);
    prev->input = pipefd[0];
    if (current->next->next)
    {
        prev->next = current->next->next;
        current->next->next->prev = prev;
    }
    else
        prev->next = NULL;
    free(current->next->value);
    free(current->next);
    free(current->value);
    free(current);
    return (prev);
}

void    fill_pipe_position(t_list *current)
{
    while (current)
    {
        if (current->pipe == 1)
        {
            if (current->prev == NULL || current->prev->pipe == 0)
                current->pipe_position = 1;
            else if (current->prev->pipe == 1 && (current->next == NULL || current->next->pipe == 0))
                current->pipe_position = 3;
            else if (current->prev->pipe == 1 && current->next->pipe == 1)
                current->pipe_position = 2;
        }
        current = current->next;
    }
}

void    open_fds_and_pipes(t_list *head)
{
    t_list *current;

    current = head;
    while (current)
    {
        if (ft_strncmp(current->value, "|\0", 1) == 0) 
		    current = handle_pipe(current);
	    else if (ft_strncmp(current->value, "<<\0", 2) == 0)
		    current = handle_heredoc(current);
	    else if (ft_strncmp(current->value, ">>\0", 2) == 0)
		    current = handle_redirection_out_append(current);
	    else if (ft_strncmp(current->value, "<\0", 1) == 0)
		    current = handle_redirection_in(current);
	    else if (ft_strncmp(current->value, ">\0", 1) == 0)
		    current = handle_redirection_out(current);
        current = current->next;
    }
    fill_pipe_position(head);
}