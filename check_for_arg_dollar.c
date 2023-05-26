/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_arg_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:18:26 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 18:18:29 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_flag(char arg, int flag)
{
	if (arg == '\"' && flag != 1)
		flag = flag_status(flag);
	if (flag == 0 || flag == 1)
		flag = handle_single_quotes_args(arg, flag);
	return (flag);
}

int	should_proccess_var(char *arg, int i, int flag)
{
	return (arg[i] == '$' && (arg[i + 1] != '\"' \
	&& arg[i + 1] != '\'') && (flag == 0 || flag == 2));
}

int	should_proccess_quote_var(char *arg, int i, int flag)
{
	return (arg[i] == '$' && (arg[i + 1] == '\"' \
	|| arg[i + 1] == '\'') && (flag == 0 || flag == 2));
}

char	*process_arg(char *arg, int status, t_list *current, int len)
{
	int		flag;
	int		i;
	char	*new_value;

	flag = 0;
	i = 0;
	new_value = ft_calloc(1, sizeof(char));
	while (i < len)
	{
		flag = handle_flag(arg[i], flag);
		if (arg[i] == '$' && arg[i + 1] == '?' && (flag == 0 || flag == 2))
			new_value = process_status_value(new_value, status, &i);
		else if (should_proccess_var(arg, i, flag))
			new_value = process_environment_variable(new_value, arg, &i);
		else if (should_proccess_quote_var(arg, i, flag))
			new_value = process_quoted_string(new_value, arg, &i, current);
		else
		{
			new_value = char_join(new_value, arg[i], current);
			i++;
		}
	}
	return (new_value);
}

void	check_args_for_dollar(t_list *current, int status)
{
	int		j;
	char	*new_value;

	j = 0;
	while (j < current->argc)
	{
		if (check_for_dollar(current->args[j]) && \
		check_for_quote_dollar(current->args[j]))
		{
			new_value = process_arg(current->args[j], status, \
			current, ft_strlen(current->args[j]));
			free(current->args[j]);
			current->args[j] = new_value;
		}
		j++;
	}
}
