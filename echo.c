#include "minishell.h"

int n_definer(char *arg)
{
	int j = 1;
	int seen_n = 0;

	if (!arg)
		return (0);
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		if (arg[2] != 'n' &&  arg[2] == '\0')
			return (1);
		while (arg[j] == 'n')
		{
			j++;
			if (arg[j] == '\0')
				return (1);
			if (arg[j] != 'n')
				seen_n = 1;
			else if (seen_n)
				return (0);
		}
	}
	return (0);
}

int one_n_checker(t_list *echo)
{
	if (echo->argc < 1)
		return(printf("\n"));
	if (echo->argc == 1)
	{
		if (n_definer(echo->args[0]) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

int ft_echo(t_list *echo)
{
	int i;
	int n_flag;
	char *string;

	n_flag = 0;
	i = 0;
	if (echo->argc == 0)
		return (0);
	int original_fd = dup(STDOUT_FILENO);
	dup2(echo->output, STDOUT_FILENO);
	if (one_n_checker(echo) == 1)
		return (0);
	// printf("nflag = %d && argc = %d\n", n_flag, echo->argc);
	while(n_definer(echo->args[n_flag]) == 1)
		n_flag++;

	if (echo->argc <= n_flag)
		return (0);	
	i = n_flag;
	string = ft_calloc((echo->argc - n_flag), sizeof(char));
	ft_strcat(string, echo->args[i]);
	i++;
	while(i < echo->argc)
	{
		ft_strcat(string, " ");
		ft_strcat(string, echo->args[i]);
		i++;
	}
	printf("%s", string);
	if(n_flag == 0)
		printf("\n");
	dup2(original_fd, STDOUT_FILENO);
	close(original_fd);
	return (0);
}
