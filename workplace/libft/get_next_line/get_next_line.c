/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:30:00 by kei2003730       #+#    #+#             */
/*   Updated: 2025/07/01 13:30:00 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1024

static char	*read_until_newline(int fd, char *leftover)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(leftover, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(leftover, buffer);
		free(leftover);
		leftover = temp;
		if (!leftover)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (leftover);
}

static char	*extract_line(char *leftover)
{
	char	*line;
	int		i;

	if (!leftover || !leftover[0])
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_leftover(char *leftover)
{
	char	*new_leftover;
	int		i;
	int		j;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	i++;
	new_leftover = malloc(ft_strlen(leftover) - i + 1);
	if (!new_leftover)
		return (NULL);
	j = 0;
	while (leftover[i])
		new_leftover[j++] = leftover[i++];
	new_leftover[j] = '\0';
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
	{
		leftover = malloc(1);
		if (!leftover)
			return (NULL);
		leftover[0] = '\0';
	}
	leftover = read_until_newline(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	leftover = update_leftover(leftover);
	return (line);
}
