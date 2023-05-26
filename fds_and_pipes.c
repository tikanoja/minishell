#include "minishell.h"

t_list *free_redirection_out(t_list *current, t_list *prev, t_list *next)
{
	t_list *ret;
	int i;

	ret = NULL;
	i = 0;
	if (prev && next && next->next)
	{
		prev->next = next->next;
		next->next->prev = prev;
		ret = next->next;
	}
	else if (!prev && next && next->next)
	{
		next->next->prev = NULL;
		ret = next->next;
	}
	else if ((prev && next && !next->next) || (prev && !next))
	{
		prev->next = NULL;
		ret = NULL;
	}
	while(prev && current->next && current->next->args &&\
	current->next->args[i])
	{
		current->prev->args = realloc_array(current->prev, current->next->args[i], NULL, NULL);
		free(current->next->args[i]);
		i++;
	}
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
	return (ret);
}

int redirection_directory_check(char *str)
{
	struct stat file_info;

	if (stat(str, &file_info) == 0)//protect?
	{
		if (S_ISDIR(file_info.st_mode))
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": is a directory\n", 2);
		}
		else if(S_ISREG(file_info.st_mode) && access(str, X_OK) != 0)
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
	else
	{
		ft_putstr_fd("shelly: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (0);
}

t_list    *handle_redirection_out(t_list *current)
{
	t_list *prev;
	t_list *next;
	int fd;

	prev = current->prev;
	next = current->next;
	if (!next)
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
		if (fd == -1 && prev->execflag != 1)
		{
			redirection_directory_check(next->value);
			if (prev)
				prev->execflag = 1;
		}
		if (prev && prev->execflag != 1)
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
	if (!next)
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
		if (access(next->value, F_OK) == -1 && prev->execflag != 1)
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
			if (fd == -1 && prev->execflag != 1)
			{
				printf("error opening file %s\n", next->value);
				if (prev)
					prev->execflag = 1;
			}
			else
			{
				if (prev && prev->execflag != 1)
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
	if (!next)
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
		if (fd == -1 && prev->execflag != 1)
		{
			redirection_directory_check(next->value);
			if (prev)
				prev->execflag = 1;
		}
		if (prev && prev->execflag != 1)
			prev->output = fd;
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

void fill_node_from_split(t_list *new, char *input)
{
	char **arr;
	int i;

	i = 1;
	arr = ft_split(input, ' ');
	free(input);
	new->value = ft_strdup(arr[0]);
	free(arr[0]);
	while(arr[i])
	{
		new->args = realloc_array(new, arr[i], NULL, NULL); // mita jos pitaa fill useempi node?
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *parse_stdin_input(char *input)
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

t_list	*fill_node_from_stdin(t_list *current)
{
	t_list *new;
	char *input;
	new = ft_calloc(1, sizeof(t_list)); //protect
	new->argc = 0;
	new->pipe = 1;
	new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
	new->prev = current;
	new->next = NULL;
	new->args = NULL;
	new->execflag = 0;
	input = readline(">"); // ehk pitaa lisaa splitti!
	input = parse_stdin_input(input);
	if (ft_strlen(input) == 0)
	{
		free(new);
		free(input);
		return(NULL);
	}
	if (fill_node_split_check(input) == 1)
		fill_node_from_split(new, input);
	else
	{
		new->value = ft_strdup(input);
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
		printf("error opening pipe\n"); //protect
	if (prev && prev->output == STDOUT_FILENO) // toi jalkimmainen arg fiksas echo moi > testfile | cat -e
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
int	is_it_quote(char c)
{
	if(c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}
char	*heredoc_env_open(char *input)
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

t_list	*end_heredoc(t_list *current, int pipefd[2])
{
	t_list  *prev;
	t_list  *ret;
	//t_list	*new;
	int i;

	i = 0;
	ret = NULL;
	prev = current->prev;
	if (prev)
		prev->input = pipefd[0];
	else
		close(pipefd[0]);
	if (current->next && current->next->next && prev)
	{
		prev->next = current->next->next;
		current->next->next->prev = prev;
		ret = current->next->next;
	}
	else if (!current->next && !current->next->next && prev)
		prev->next = NULL;
	else if (current->next && current->next->next && !prev)
	{
		current->next->next->prev = NULL;
		ret = current->next->next;
	}
	else if (current->next && !current->next->next && prev)
		prev->next = NULL;
	while(current->next && current->next->args && current->next->args[i])
	{
		if (prev == NULL)
		{
			prev = add_node(NULL, current->next->args[i], NULL, NULL);
			prev->next = ret;
			if (ret != NULL)
				ret->prev = prev;
			current->prev = prev;
			ret = current->prev;
		}
		else if (prev)
		{
			current->prev->args = realloc_array(current->prev, current->next->args[i], NULL, NULL);
			free(current->next->args[i]);
		}
		i++;
	}
	if (current->next)
		free(current->next->value);
	if (current->next)
		free(current->next);
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
	return (ret);
}

int	last_try_static_c(int flag)
{
	static int status;
	if (flag == -1)
		status = 0;
	if (flag == 1)
		status = 1;
	return (status);
}

void	heredoc_signal_c(int signum __attribute__((unused)))
{
	last_try_static_c(1);
	rl_on_new_line();
	rl_redisplay();
}

t_list	*handle_heredoc(t_list *current)
{
	char	*delim;
	char	*input;
	int		pipefd[2];
	
	last_try_static_c(-1);
	signal(SIGINT, SIG_IGN);
	if (!current->next)
	{
		ft_putstr_fd("shelly: syntax error near unexpected token `newline'", 2);
		if (current->prev)
			current->prev->execflag = 1;
	}
	else
	{
		termios_handler(1);
		signal(SIGINT, heredoc_signal_c);
		delim = ft_strdup(current->next->value);
		if (pipe(pipefd) == -1)
			printf("error opening heredoc pipe\n");
		while(1)
		{
			if (last_try_static_c(0) == 1)
			{
				free_list(get_head_node(current));
				close(pipefd[1]);
				run_minishell();
			}
			else
				input = readline(">");
			if (!input)
			{
				printf("\033[1A> ");
				break;
			}
			if ((ft_strncmp(input, delim, ft_strlen(delim)) == 0 && input[ft_strlen(delim)] == '\0'))
			{
				free(input);
				break ;
			}
			if(check_for_dollar(input) == 1)
				input = heredoc_env_open(input);
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