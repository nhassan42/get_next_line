/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhassan <nhassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:50:18 by nhassan           #+#    #+#             */
/*   Updated: 2024/05/05 21:46:49 by nhassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_a_line(int fd, char *remainder, char *buff)
{
	ssize_t	readbytes;
	char	*tmp;

	readbytes = 1;
	while (readbytes > 0)
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(remainder);
			return (NULL);
		}
		else if (readbytes == 0)
			break ;
		buff[readbytes] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		tmp = remainder;
		remainder = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (remainder);
}

char	*trim_line(char *line_buffer)
{
	ssize_t	i;
	char	*remainder;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	remainder = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remainder);
		buff = NULL;
		remainder = NULL;
		return (NULL);
	}
	buff = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	line = get_a_line(fd, remainder, buff);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	remainder = trim_line(line);
	return (line);
}
