/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value_for_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:08:28 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 18:24:21 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_value_for_dollar(t_list *current, int status)
{
	char	*new_value;

	if (check_for_dollar(current->value) && \
	check_for_quote_dollar(current->value))
	{
		new_value = process_arg(current->value, status, \
		current, ft_strlen(current->value));
		free(current->value);
		if (*new_value == '\0')
			new_value = NULL;
		current->value = new_value;
		if (current->value == NULL)
			current->execflag = 1;
	}
}
