#include "minishell.h"

t_list *free_redirection_out(t_list *current, t_list *prev, t_list *next)
{
    t_list *ret;

    ret = NULL;
    if (prev && next && next->next)
    {
        prev->next = next->next;
        next->next->prev = prev;
        ret = next->next;
    }
    else if ((prev && next && !next->next) || (prev && !next))
    {
        prev->next = NULL;
        ret = NULL;
    }
    else if (!prev && next && next->next)
    {
        next->next->prev = NULL;
        ret = next->next;
    }
    free(current->value);
    current->value = NULL;
    free(current);
    if (next)
    {
        free(next->value);
        next->value = NULL;
        free(next);
    }
    return (ret);
}

t_list    *handle_redirection_out(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
    {
        write(2, "shelly: syntax error near unexpected token 'newline'\n", 53);
        if (prev)
            prev->execflag = 1;
    }
    else if (is_it_redirection(next->value) > 0)
    {
        ft_putstr_fd("shelly: syntax error near unexpected token '", 2);
        ft_putstr_fd(next->value, 2);
        ft_putstr_fd("'\n", 2);
        if (prev)
            prev->execflag = 1;
    }
    else
    {
        fd = open(next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            printf("error opening file %s\n", next->value);
        if (prev)
            prev->output = fd;
        else
            close(fd);
    }
    return (free_redirection_out(current, prev, next));
}

t_list    *handle_redirection_in(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
    {
        write(2, "shelly: syntax error near unexpected token 'newline'\n", 53);
        if (prev)
            prev->execflag = 1;
    }
    else if (is_it_redirection(next->value) > 0)
    {
        ft_putstr_fd("shelly: syntax error near unexpected token '", 2);
        ft_putstr_fd(next->value, 2);
        ft_putstr_fd("'\n", 2);
        if (prev)
            prev->execflag = 1;
    }
    else
    {
        if (access(next->value, F_OK) == -1)
        {
            ft_putstr_fd("shelly: ", 2);
            ft_putstr_fd(next->value, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            if (prev)
                prev->execflag = 1;
        }
        else
        {
            fd = open(next->value, O_RDONLY, 0644);
            if (fd == -1)
            {
                printf("error opening file %s\n", next->value);
                if (prev)
                    prev->execflag = 1;
            }
            else
            {
                if (prev)
                    prev->input = fd;
                else
                    close(fd);
            }
        }
    }
    return (free_redirection_out(current, prev, next)); //pitäis toimii täs mut jos ei ni pitää tehä oma hehheh
}

t_list    *handle_redirection_out_append(t_list *current)
{
    t_list *prev;
    t_list *next;
    int fd;

    prev = current->prev;
    next = current->next;
    if (!next || !next->value || ft_strlen(next->value) == 0)
    {
        write(2, "shelly: syntax error near unexpected token 'newline'\n", 53);
        if (prev)
            prev->execflag = 1;
    }
    else if (is_it_redirection(next->value) > 0)
    {
        ft_putstr_fd("shelly: syntax error near unexpected token '", 2);
        ft_putstr_fd(next->value, 2);
        ft_putstr_fd("'\n", 2);
        if (prev)
            prev->execflag = 1;
    }
    else
    {
        fd = open(next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            printf("error opening file %s\n", next->value);
        if (prev)
            prev->output = fd;
        else
            close(fd);
    }
    return (free_redirection_out(current, prev, next));
}

t_list *fill_node_from_stdin(t_list *current)
{
    t_list *new;

    new = malloc(sizeof(t_list)); //protect
    new->args = malloc(sizeof(char **)); //protect
    new->args[0] = NULL;
    new->argc = 0;
    new->pipe = 1;
    new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
    new->prev = current;
    new->next = NULL;
    new->value = readline(">"); // ehk pitaa lisaa splitti!
    return (new);
}

t_list *free_pipe(t_list *current, t_list *prev, t_list *next)
{
    if (prev)
        prev->next = next;
    next->prev = prev;
    free(current->value);
    free(current);
    if (next->next)
        return (next->next);
    else
        return (NULL);
}

t_list    *handle_pipe(t_list *current)
{
    t_list *prev;
    t_list *next;
    int pipefd[2];
    int syntaxflag;

    syntaxflag = 0;
    prev = current->prev;
    next = current->next;
    if (!prev)
        ft_putstr_fd("shelly: syntax error near unexpected token `|'", 2); //ja mitaan ei tapahdu paitsi taa error msg
    if (!next || !next->value || ft_strlen(next->value) == 0)
        next = fill_node_from_stdin(current);
    if (pipe(pipefd) == -1)
        printf("error opening pipe\n"); //protect
    if (prev)
    {
        prev->output = pipefd[1];
        prev->pipe = 1;
    }
    else
        close (pipefd[1]);
    next->input = pipefd[0];
    next->pipe = 1;
    return (free_pipe(current, prev, next));
}
int is_it_quote(char c)
{
    if(c == '\'' || c == '\"')
        return (1);
    else
        return (0);
}
char    *heredoc_env_open(char *input)
{
    char    input_env[1024];
    char    *input_opened;
    int     i;
    int     j;

    i = 0;
    j = 0;
    input_opened = malloc(1);
    ft_bzero(input_env, 1024);
    while(input[i])
    {
        //flag = 1;
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
    free(input);
    input = ft_strdup(input_opened);
    free(input_opened);
    return(input);
}

t_list *end_heredoc(t_list *current, int pipefd[2])
{
    t_list  *prev;

    prev = current->prev;
    if (prev)
        prev->input = pipefd[0];
    else
        close(pipefd[0]);
    if (current->next && current->next->next && prev)
    {
        prev->next = current->next->next;
        current->next->next->prev = prev;
    }
    else if (!current->next && !current->next->next && prev)
        prev->next = NULL;
    else if (current->next->next && !prev)
        current->next->next->prev = NULL;
    if (current->next)
        free(current->next->value);
    if (current->next)
        free(current->next);
    free(current->value);
    free(current);
    return (prev);
}

t_list  *handle_heredoc(t_list *current)
{
    char    *delim;
    char    *input;
    int     pipefd[2];
    
    if (!current->next)
    {
        ft_putstr_fd("shelly: syntax error near unexpected token `newline'", 2);
        if (current->prev)
            current->prev->execflag = 1;
    }
    else
    {
        delim = ft_strdup(current->next->value);
        if (pipe(pipefd) == -1)
            printf("error opening heredoc pipe\n");
        while(1)
        {
            init_heredoc_signals();
            input = readline(">");
            if (!input)
            {
                printf("\033[1A> ");
                break;
            }
            if(check_for_dollar(input) == 1)
                input = heredoc_env_open(input);
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
    }
    return (end_heredoc(current, pipefd));
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
        else
            current = current->next;
    }
}