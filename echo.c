#include "minishell.h"

int n_definer(char *arg)
{
	int	j;

	j = 1;
	if (ft_strncmp(arg, "-n", 2) == 0)
    {
        if (arg[2] != 'n' && (is_it_whitespace(arg[2]) == 1 || arg[2] == '\0'))
            return (1);
        while (arg[j] == 'n')
        {
            j++;
            if (is_it_whitespace(arg[j]) == 1 || arg[j] == '\0')
				return (1);
			if (arg[j] != 'n')
				return (0);
        }
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
	if (echo->argc < 1)
		printf("\n");
	while(n_definer(echo->args[n_flag]) == 1)
		n_flag++;
	i = n_flag;
	string = malloc(sizeof(char) * (echo->argc - n_flag));
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
	return (0);
}

void ft_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd); 
	else
	{
        perror("getcwd() error");
        exit (EXIT_FAILURE);
    }
}

void ft_exit(int exit_status)
{
    exit_status = exit_status % 256;
    exit (exit_status);
}
/*int main()
{
	t_list *echos;
	echos = malloc(sizeof(t_list) * 1);
	echos->value = "echo"; //esim "echo", ">" taiii "file.txt"
	char *args[20] = {"-n","-n","hello world","hello $ECHOagain", "fucker"}; //esim "-n" ja "terve $ARG"
	echos->args = args;
	echos->argc = 5; //you already know
	echos->input = 0; //fd for input
	echos->output = 0; //fd for output
	echos->append = 0; //flag if output redirection should append to file
	echos->background = 0; //ei oo mitää hajuu
	echo (echos);
	pwd();
	free(echos);
}*/