/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:18 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 12:57:25 by jaurasma         ###   ########.fr       */
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

void	print_error_sys_cmd(t_list *current)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(current->value, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	if_check_for_sys_cmd(t_list *current)
{
	if (is_it_builtin(current->value) == 0 && \
	variable_assign_check(current->value) == 0 && \
	slash_check(current->value) == 0)
		return (1);
	return (0);
}

char	**patharr_split(int *pathflag, t_list *current)
{
	char	**patharr;

	patharr = ft_split(envcpy[*pathflag] + 5, ':');
	if (patharr == NULL)
		exit_gracefully(current);
	*pathflag = 0;
	return (patharr);
}

void	parse_system_commands(t_list *head, int pathflag)
{
	char	**patharr;
	t_list	*current;

	pathflag = findpath(envcpy);
	current = head;
	if (pathflag != -1)
		patharr = patharr_split(&pathflag, current);
	while (current)
	{
		if (current->value[0] == '\0' || current->value == NULL)
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
