/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:18 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 00:23:36 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pathflag_is_zero(t_list *current, char **patharr)
{
	convert_to_lowercase(current->value);
	move_value_to_args(current);
	if (access(current->value, F_OK) != 0)
		current->value = get_path(patharr, current->args[0]);
	if (current->value == NULL)
		current->system_command = -1;
	else
		current->system_command = 1;
}

int	is_it_builtin_sys(char *prompt)
{
	if (ft_strncmp_casein(prompt, "echo\0", 5) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "cd\0", 3) == 0 && \
	(is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "pwd\0", 4) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "export\0", 7) == 0 && \
	(is_it_whitespace(prompt[6]) || prompt[6] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "unset\0", 6) == 0 && \
	(is_it_whitespace(prompt[5]) || prompt[5] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "env\0", 4) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "exit\0", 5) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	return (0);
}

int	if_check_for_sys_cmd(t_list *current)
{
	struct stat	file_info;

	if (stat(current->value, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			redir_directory_check_prints(current->value, 1);
			current->execflag = 1;
			return (1);
		}
	}
	if (is_it_builtin_sys(current->value) == 0 && \
	variable_assign_check(current->value) == 0)
		return (1);
	return (0);
}

char	**patharr_split(int *pathflag, t_list *current)
{
	char	**patharr;

	patharr = ft_split(g_envcpy[*pathflag] + 5, ':');
	if (patharr == NULL)
		exit_gracefully(current);
	*pathflag = 0;
	return (patharr);
}

void	parse_system_commands(t_list *head, int pathflag)
{
	char	**patharr;
	t_list	*current;

	pathflag = findpath(g_envcpy);
	current = head;
	if (pathflag != -1)
		patharr = patharr_split(&pathflag, current);
	while (current)
	{
		if (current->value == NULL || current->value[0] == '\0')
		{
			current = current->next;
			continue ;
		}
		if (if_check_for_sys_cmd(current) == 1)
		{
			if (pathflag == 0)
				pathflag_is_zero(current, patharr);
			else
				print_error_sys_cmd(current);
		}
		current = current->next;
	}
	if (pathflag != -1)
		free_split(patharr);
}
