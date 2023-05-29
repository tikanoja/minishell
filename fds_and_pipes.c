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

void	redir_directory_check_prints(char *str, int flag)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(": is a directory\n", 2);
	else if (flag == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (flag == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
}

int redir_directory_check(char *str, t_list *prev)
{
	struct stat file_info;

	if (stat(str, &file_info) == 0)//protect?
	{
		if (S_ISDIR(file_info.st_mode))
		{
			if (prev == NULL || (prev && prev->execflag != 1))
				redir_directory_check_prints(str, 1);
			return (1);
		}
		else if(S_ISREG(file_info.st_mode) && access(str, X_OK) != 0)
		{
			if (prev == NULL || (prev && prev->execflag != 1))
				redir_directory_check_prints(str, 2);
			return (1);
		}
	}
	else
	{
		if (prev == NULL || (prev && prev->execflag != 1))
			redir_directory_check_prints(str, 3);
		return (1);
	}
	return (0);
}

void	redir_out_null_next(t_list *prev)
{
	write(2, "shelly: syntax error near unexpected token 'newline'\n", 53);
	if (prev)
		prev->execflag = 1;
}

void	redir_out_double_redir(t_list *prev, t_list *next)
{
	ft_putstr_fd("shelly: syntax error near unexpected token '", 2);
	ft_putstr_fd(next->value, 2);
	ft_putstr_fd("'\n", 2);
	if (prev)
		prev->execflag = 1;
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

int fill_node_split_check(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void fill_node_from_split(t_list *new, char *input, t_list *current)
{
	char **arr;
	int i;

	i = 1;
	arr = ft_split(input, ' ');
	if (!arr)
	{
		free_split(arr);
		exit_gracefully(current);
	}
	free(input);
	new->value = ft_strdup(arr[0]);
	if (!new->value)
	{
		free_split(arr);
		exit_gracefully(current);
	}
	free(arr[0]);
	while(arr[i])
	{
		new->args = realloc_array(new, arr[i], NULL, NULL); // mita jos pitaa fill useempi node?
		if (!new->args)
			exit_gracefully(current);
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *parse_stdin_input(char *input, t_list *current)
{
	int start;
	int end;
	int i;
	char *new;

	start = 0;
	end = ft_strlen(input) - 1;
	i = 0;
	while(is_it_whitespace(input[start]) == 1)
		start++;
	while(is_it_whitespace(input[end]) == 1)
		end--;
	if ((size_t)(end - start) == ft_strlen(input) - 1)
		return(input);
	new = ft_calloc(end - start + 1, sizeof(char));
	if (!new)
		exit_gracefully(current);
	new[end + 1] = '\0';
	while (start <= end)
	{
		new[i] = input[start];
		i++;
		start++;
	}
	free(input);
	return(new);
}

void	*free_empty_stdin_input(char *input, t_list *new)
{
	free(new);
	free(input);
	return(NULL);
}

t_list	*fill_node_from_stdin(t_list *current)
{
	t_list *new;
	char *input;
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		exit_gracefully(current);
	new->argc = 0;
	new->pipe = 1;
	new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
	new->prev = current;
	new->next = NULL;
	new->args = NULL;
	new->execflag = 0;
	input = readline(">"); // ehk pitaa lisaa splitti!
	input = parse_stdin_input(input, current);
	if (ft_strlen(input) == 0)
		return (free_empty_stdin_input(input, new));
	if (fill_node_split_check(input) == 1)
		fill_node_from_split(new, input, current);
	else
	{
		new->value = ft_strdup(input);
		if (!new->value)
			exit_gracefully(current);
		free(input);
	}
	return (new);
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
