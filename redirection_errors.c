/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:42:13 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:42:58 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_directory_check_prints(char *str, int flag)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(": is a directory\n", 2);
	else if (flag == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (flag == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
}

void	redir_out_null_next(t_list *prev)
{
	write(2, "shelly: syntax error near unexpected token 'newline'\n", 53);
	if (prev)
		prev->execflag = 1;
}

void	redir_out_double_redir(t_list *prev, t_list *next)
{
	ft_putstr_fd("shelly: syntax error near unexpected token '", 2);
	ft_putstr_fd(next->value, 2);
	ft_putstr_fd("'\n", 2);
	if (prev)
		prev->execflag = 1;
}

int	redir_directory_check(char *str, t_list *prev)
{
	struct stat	file_info;

	if (stat(str, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			if (prev == NULL || (prev && prev->execflag != 1))
				redir_directory_check_prints(str, 1);
			return (1);
		}
		else if (S_ISREG(file_info.st_mode) && access(str, X_OK) != 0)
		{
			if (prev == NULL || (prev && prev->execflag != 1))
				redir_directory_check_prints(str, 2);
			return (1);
		}
	}
	else
	{
		if (prev == NULL || (prev && prev->execflag != 1))
			redir_directory_check_prints(str, 3);
		return (1);
	}
	return (0);
}
