#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*typedef struct  s_list
{
	// enum t_tokenType; //COMMAND, PIPE, REDIRECTION etc...
	// enum builtinCommand;
	char *value; //esim "echo", ">" taiii "file.txt"
	char **args; //esim "-n" ja "terve $ARG"
	int argc; //you already know
	int input; //fd for input
	int output; //fd for output
	int append; //flag if output redirection should append to file
	int background; //ei oo mitää hajuu
	struct s_list *next; //next node
	struct s_list *prev; //prev node
}               t_list;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int is_it_whitespace(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	else
		return (0);
}

char *ft_strcat(char *dest, const char *src)
{
	char *result; 
	
	result = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (result);
}*/

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