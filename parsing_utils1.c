#include "minishell.h"

void	init_parsecmd(t_list **node, t_list **head, int *argflag)
{
	*node = NULL;
	*head = NULL;
	*argflag = -1;
}

t_list	*get_head_node(t_list *node)
{
	if (node == NULL)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}

void	parse_redir(int *argflag, t_list **node, char **token, t_list **head)
{
	*argflag = -1;
	*node = add_node(*node, *token, envcpy, *head);
	free(*token);
	*token = ft_lexer(NULL, envcpy, *head);
}

void	handle_parsing_end(int *argflag, char **token, t_list **head)
{
	*argflag = *argflag + 1;
	free(*token);
	*token = ft_lexer(NULL, envcpy, *head);
}

void	free_token_and_prompt(char **prompt, char **token)
{
	free(*prompt);
	if (*token)
		free(*token);
}