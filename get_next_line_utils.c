/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:13:48 by utenret           #+#    #+#             */
/*   Updated: 2022/11/23 14:17:04 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	s = malloc(len1 + len2 + 1);
	if (s != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(s, s1, len1 + 1);
		if (s2 != NULL)
			ft_strlcpy(s + len1, s2, len2 + 1);
	}
	if (s1 != NULL)
		free(s1);
	return (s);
}

char	*ft_strnjoin(char *s1, char *s2, int size)
{
	char	*s;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	s = malloc(len1 + size + 1);
	if (s != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(s, s1, len1 + 1);
		if (s2 != NULL)
			ft_strlcpy(s + len1, s2, size + 1);
	}
	if (s1 != NULL)
		free(s1);
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (size > 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		dest[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
