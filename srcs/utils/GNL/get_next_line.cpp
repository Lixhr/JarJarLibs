/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:18:12 by cbeaufil          #+#    #+#             */
/*   Updated: 2024/10/31 09:41:26 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "GNL.hpp"

static char	*extract_line(char *stored_buffer)
{
	size_t	i;

	if (!stored_buffer)
		return (NULL);
	i = 0;
	while (stored_buffer[i] && stored_buffer[i] != '\n')
		i++;
	if (stored_buffer[i] == '\n')
		return (gnl_substr(stored_buffer, 0, i + 1));
	return (NULL);
}

static char	*new_read(int fd, ssize_t *bytes_read, char *stack_buf, char *line)
{
	char	*file_content;

	file_content = (char *)malloc(BUFFER_SIZE + 1);
	if (!file_content)
		return (NULL);
	*bytes_read = read(fd, file_content, BUFFER_SIZE);
	if (*bytes_read == -1)
		free(line);
	if (*bytes_read < 1)
	{
		stack_buf[0] = 0;
		free(file_content);
		return (NULL);
	}
	file_content[*bytes_read] = 0;
	return (file_content);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*read_until_nl(char *stack_buffer, int fd)
{
	char	*line;
	char	*batch;
	ssize_t	bytes_read;

	line = NULL;
	if (*stack_buffer)
		line = gnl_strdup(stack_buffer);
	while (1)
	{
		batch = new_read(fd, &bytes_read, stack_buffer, line);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			return (line);
		if (gnl_strchr(batch, '\n'))
			break ;
		line = gln_strjoin(line, batch);
	}
	ft_strlcpy(stack_buffer, batch, BUFFER_SIZE +1);
	line = gln_strjoin(line, batch);
	batch = extract_line(line);
	free(line);
	if (*batch)
		return (batch);
	return (NULL);
}

char	*GNL::get_next_line()
{
	size_t		i;

	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		this->buffer[0] = '\0';
		return (NULL);
	}
	i = 0;
	while (this->buffer[i] && this->buffer[i] != '\n')
		i++;
	if (this->buffer[i])
		ft_strlcpy(buffer, &buffer[i + 1], BUFFER_SIZE +1);
	i = 0;
	while (this->buffer[i] && this->buffer[i] != '\n')
		i++;
	if (this->buffer[i])
		return (extract_line(this->buffer));
	return (read_until_nl(this->buffer, fd));
}
