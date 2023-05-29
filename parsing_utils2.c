#include "minishell.h"

int	ft_strncmp_casein(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] >= 65 && s1[i] <= 90 && s1[i] + 32 == s2[i])
			i++;
		else
			break ;
	}
	if (s1[i] >= 65 && s1[i] <= 90)
		return ((unsigned char)s1[i] + 32 - (unsigned char)s2[i]);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_it_builtin(char *prompt)
{
	if (ft_strncmp_casein(prompt, "echo\0", 4) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "cd\0", 2) == 0 && \
	(is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "pwd\0", 3) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "export\0", 6) == 0 && \
	(is_it_whitespace(prompt[6]) || prompt[6] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "unset\0", 5) == 0 && \
	(is_it_whitespace(prompt[5]) || prompt[5] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "env\0", 3) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "exit\0", 4) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	return (0);
}

int	is_it_redirection(char *prompt)
{
	if (prompt == NULL)
		return (0);
	else if (ft_strncmp(prompt, "|\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, "<<\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">\0", 2) == 0)
		return (1);
	return (0);
}

int	is_it_redirection_parsing(char *prompt)
{
	if (ft_strncmp(prompt, "|", 1) == 0)
		return (1);
	else if (ft_strncmp(prompt, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">", 1) == 0)
		return (1);
	return (0);
}

int	is_it_log_operator(char *prompt)
{
	if (ft_strncmp(prompt, "||\0", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, "&&\0", 2) == 0)
		return (2);
	return (0);
}
