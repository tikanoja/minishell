/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:52:21 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/02/12 10:51:33 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*cut_temp(char *temp, char *line)
{
	int	i;
	int	nli;

	if (line == NULL)
	{
		free(temp);
		temp = NULL;
		return (0);
	}
	i = 0;
	nli = find_nl(temp) + 1;
	if (nli == 0)
		nli = -1;
	while (temp[nli + i] && nli != -1)
	{
		temp[i] = temp[nli + i];
		i++;
	}
	while (temp[i])
	{
		temp [i] = '\0';
		i++;
	}
	return (temp);
}

char	*cut_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	while (line[i])
	{
		line[i] = '\0';
		i++;
	}
	return (line);
}

char	*readfile(int fd, char *temp, int *adv)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	*adv = read(fd, buf, BUFFER_SIZE);
	if (*adv == -1)
	{
		free(temp);
		temp = NULL;
		free(buf);
		buf = NULL;
		return (NULL);
	}
	buf[*adv] = '\0';
	temp = gnl_strjoin(temp, buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	int			adv;

	adv = 1;
	if (temp == NULL)
		temp = ft_calloc(BUFFER_SIZE + 1, sizeof(int));
	if (temp == NULL || fd < 0 || BUFFER_SIZE < 1)
		adv = -1;
	while (adv > -1)
	{
		temp = readfile(fd, temp, &adv);
		if (temp == NULL || temp[0] == '\0')
			break ;
		if (find_nl(temp) != -1 || adv != BUFFER_SIZE)
		{
			line = cut_line(ft_strdup(temp));
			temp = cut_temp(temp, line);
			return (line);
		}
	}
	free(temp);
	temp = NULL;
	return (NULL);
}
