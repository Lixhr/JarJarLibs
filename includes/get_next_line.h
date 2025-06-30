/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:25:04 by cbeaufil          #+#    #+#             */
/*   Updated: 2024/10/30 17:20:10 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
#define BUFFER_SIZE 1024
#include "GNL.hpp"


typedef unsigned char	t_byte;
size_t	ft_strlen(const char *c);
char	*gnl_strdup(const char *s);
char	*gln_strjoin(char *s1, char *s2);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif
