/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:28:44 by cbeaufil          #+#    #+#             */
/*   Updated: 2024/10/31 09:35:48 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] && i < (size -1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, len + 2);
	return (dest);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char		*dest;
	size_t		s_len;
	size_t		dest_len;	

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (gnl_strdup(""));
	dest_len = len;
	if ((s_len - start) < len)
		dest_len = s_len - start;
	dest = (char *)malloc(dest_len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[start], dest_len + 1);
	return (dest);
}

char	*gln_strjoin(char *line, char *batch)
{
	size_t	i;
	size_t	y;
	char	*dest;

	dest = (char *)malloc(ft_strlen(line) + ft_strlen(batch) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	if (line)
	{
		while (line[i])
		{
			dest[i] = line[i];
			i++;
		}
	}
	y = 0;
	while (batch[y])
		dest[i++] = batch[y++];
	dest[i] = 0;
	free(line);
	free(batch);
	return (dest);
}
