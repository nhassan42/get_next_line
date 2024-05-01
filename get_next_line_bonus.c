/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabilhassan <nabilhassan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:36:15 by nabilhassan       #+#    #+#             */
/*   Updated: 2024/05/01 06:41:21 by nabilhassan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		return (NULL);
	}
	line_buffer[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		*line;
	char		*buff;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	line = get_a_line(fd, remainder[fd], buff);
	remainder[fd] = trim_line(line);
	free(buff);
	if (!line)
		return (NULL);
	return (line);
}
