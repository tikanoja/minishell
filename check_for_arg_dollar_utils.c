/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_arg_dollar_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:02:25 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 12:47:03 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_status_value(char *new_value, int status, int *index, t_list *current)
{
	char	*buffer;

	buffer = ft_itoa(status);
	new_value = ft_strjoin_oe(new_value, buffer, current);
	free(buffer);
	(*index) += 2;
	return (new_value);
}

char	*process_environment_variable(char *new_value, char *arg, int *index, t_list *current)
{
	char	*env;

	(*index)++;
	env = ft_strndup(arg + (*index), get_env_len(arg + (*index)));
	if (ft_getenv(env))
		new_value = ft_strjoin_oe(new_value, ft_getenv(env), current);
	(*index) += ft_strlen(env);
	free(env);
	return (new_value);
}

char	*process_quoted_string(char *new_value, char *arg, \
int *index, t_list *current)
{
	char	quote_type;

	(*index) += 2;
	quote_type = arg[(*index) - 1];
	while (arg[*index] != quote_type)
	{
		new_value = char_join(new_value, arg[*index], current);
		(*index)++;
	}
	(*index)++;
	return (new_value);
}

int	flag_status(int flag)
{
	if (flag == 0)
		return (2);
	else
		return (0);
}

int	handle_single_quotes_args(char c, int flag)
{
	if (c == '\'' && flag == 0)
		return (1);
	else if (c == '\'' && flag == 1)
		return (0);
	return (flag);
}
