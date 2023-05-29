#include "minishell.h"

void	free_redir_out_frees(t_list *current, t_list *next)
{
	if (next)
	{
		free(next->value);
		next->value = NULL;
		if (next->args)
		{
			free(next->args);
			next->args = NULL;
		}
		free(next);
		next = NULL;
	}
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
}

void	free_redir_out_handle_nodes(int *i, t_list **prev, t_list **next, t_list **ret)
{
	(*i) = 0;
	if ((*prev) && next && (*next)->next)
	{
		(*prev)->next = (*next)->next;
		(*next)->next->prev = (*prev);
		(*ret) = (*next)->next;
	}
	else if (!prev && next && (*next)->next)
	{
		(*next)->next->prev = NULL;
		(*ret) = (*next)->next;
	}
	else if ((prev && next && !(*next)->next) || (prev && !next))
	{
		(*prev)->next = NULL;
		(*ret) = NULL;
	}	
}

t_list *free_redirection_out(t_list *current, t_list *prev, t_list *next)
{
	t_list *ret;
	int i;

	ret = NULL;
	free_redir_out_handle_nodes(&i, &prev, &next, &ret);
	while(current->next && current->next->args && current->next->args[i])
	{
		if (prev == NULL)
		{
			prev = add_node(NULL, current->next->args[i], NULL, NULL);
			if (!prev)
				exit_gracefully(current);
			prev->next = ret;
			if (ret != NULL)
				ret->prev = prev;
			current->prev = prev;
			ret = current->prev;
		}
		else if (prev)
		{
			prev->args = realloc_array(prev, next->args[i], NULL, NULL);
			if (!prev->args)
				exit_gracefully(current);
			free(current->next->args[i]);
		}
		i++;
	}
	free_redir_out_frees(current, next);
	return (ret);
}

t_list    *handle_redirection_out(t_list *current)
{
	t_list *prev;
	t_list *next;
	int fd;

	prev = current->prev;
	next = current->next;
	if (!next)
		redir_out_null_next(prev);
	else if (is_it_redirection(next->value) > 0)
		redir_out_double_redir(prev, next);
	else
	{
		fd = open(next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1 && redir_directory_check(next->value, prev) == 1 && prev)
				prev->execflag = 1;
		if (fd != -1 && prev && prev->execflag != 1)
		{
			if (prev->output != STDOUT_FILENO)
				close(prev->output);
			prev->output = fd;
		}
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
	if (!next)
		redir_out_null_next(prev);
	else if (is_it_redirection(next->value) > 0)
		redir_out_double_redir(prev, next);
	else
	{
		fd = open(next->value, O_RDONLY, 0644);
		if (fd == -1 && redir_directory_check(next->value, prev) == 1 && prev)
				prev->execflag = 1;
		if (fd != -1 && prev && prev->execflag != 1)
		{
			if (prev->input != STDIN_FILENO)
				close(prev->input);
			prev->input = fd;
		}
		else
			close(fd);
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
	if (!next)
		redir_out_null_next(prev);
	else if (is_it_redirection(next->value) > 0)
		redir_out_double_redir(prev, next);
	else
	{
		fd = open(next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 && redir_directory_check(next->value, prev) == 1 && prev)
				prev->execflag = 1;
		if (fd != -1 && prev && prev->execflag != 1)
		{
			if (prev->output != STDOUT_FILENO)
				close(prev->output);
			prev->output = fd;
		}
		else
			close(fd);
	}
	return (free_redirection_out(current, prev, next));
}

t_list	*free_pipe(t_list *current, t_list *prev, t_list *next)
{
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev && next)
		next->prev = NULL;
	else if (prev && !next)
		prev->next = NULL;
	free(current->value);
	free(current);
	if (next)
		return (next);
	else
		return (NULL);
}

t_list	*handle_pipe(t_list *current)
{
	t_list *prev;
	t_list *next;
	int pipefd[2];
	int syntaxflag;

	syntaxflag = 0;
	prev = current->prev;
	next = current->next;
	if (!next || !next->value || ft_strlen(next->value) == 0)
		next = fill_node_from_stdin(current);
	if (!next)
		return (free_pipe(current, prev, next));
	if (pipe(pipefd) == -1)
		exit_gracefully(current);
	if (prev && prev->output == STDOUT_FILENO)
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

t_list    *open_fds_and_pipes(t_list *head)
{
	t_list *current;

	current = head;
	while (current)
	{
		if (current->prev == NULL)
			head = current;
		if (current->value && ft_strncmp(current->value, "|\0", 2) == 0) 
			current = handle_pipe(current);
		else if (current->value && ft_strncmp(current->value, "<<\0", 3) == 0)
			current = handle_heredoc(current);
		else if (current->value && ft_strncmp(current->value, ">>\0", 3) == 0)
			current = handle_redirection_out_append(current);
		else if (current->value && ft_strncmp(current->value, "<\0", 2) == 0)
			current = handle_redirection_in(current);
		else if (current->value && ft_strncmp(current->value, ">\0", 2) == 0)
			current = handle_redirection_out(current);
		else
			current = current->next;
	}
	if(!head->value && !head->args)
		return (NULL);
	return (head);
}
