/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:44:03 by utenret           #+#    #+#             */
/*   Updated: 2022/11/23 12:16:20 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#ifndef FD
# define FD 1
#endif

char	*get_next_line(int fd);
char    **ft_split(char const *str, char c);
void    ft_cleanup(char **split);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_does_str_contains_n(char	*str);
char	*ft_strnjoin(char *s1, char *s2, int size);

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

int	ft_does_str_contains_n(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (i + 1);
	while(str[i])
	{
		i++;
		if (str[i] == '\n')
			return (i + 1);
	}
	return (-1);
}


static	char	*ft_rest(char *res, char *gnl, int i)
{
	int	c;

	c = ft_strlen(gnl);
	if (i < ft_strlen(gnl))	
	{
		res = ft_strnjoin(res, gnl, i);
		ft_strlcpy(gnl, gnl + i, BUFFER_SIZE + 1);	
		ft_memset(gnl + c, 0, BUFFER_SIZE + 1 - c);
		return (res);
	}
	else
	{ 
		res = ft_strjoin(res, gnl);
		ft_memset(gnl, 0, BUFFER_SIZE);
	return (res);
	}
}

static	char	*ft_weout(char **res, char *buf, char *gnl, int i, int c)
{
		if (i == -1)
		{
			*res = ft_strjoin(*res, buf);	
			ft_memset(buf, 0, BUFFER_SIZE);
			return (buf);
		}
		else if (i == 0)
			return (buf);
		else
		{
			ft_strlcpy(gnl, buf + i, c + 1 - i);	
			ft_memset(buf + i, 0, c - i);
			*res = ft_strjoin(*res, buf);
			ft_memset(buf, 0, BUFFER_SIZE);
			return (buf);
		}
		return (buf);
}

static	int	ft_letsread(char **res, char *buf, char *gnl, int i, int fd)
{
		int	c;

		i = ft_does_str_contains_n(buf);
		*res = ft_strjoin(*res, gnl);	
		ft_memset(gnl, 0, BUFFER_SIZE);
		while (i == -1)
		{
			c = read(fd, buf, BUFFER_SIZE);
			i = ft_does_str_contains_n(buf);
			if (c == 0)
			{
				if (*(res[0]) != '\0')
					return (0);
				free(*res);
				return (1);
			}
			if (i == -1)
				buf = ft_weout(res, buf, gnl, i, c);
		}
		if (i == 0)
			buf = ft_weout(res, buf, gnl, i, c);
		else 
			buf = ft_weout(res, buf, gnl, i, c);
		return (0);
}

char	*get_next_line(int fd)
{
	// protect against invalid fd
	static	char	gnl[BUFFER_SIZE + 1] = {0};
	char	buf[BUFFER_SIZE + 1];
	char	*res;
	int	i;

	ft_memset(buf, 0, BUFFER_SIZE + 1);
	i = ft_does_str_contains_n(gnl);
	res = NULL;	
	if (i >= 0)
		return (ft_rest(res, gnl, i));
	else if	(ft_letsread(&res, buf, gnl, i, fd) == 0)
		return (res);
	return (NULL);
}

int	main(int ac, char **av)
{
	int a;
	int i;	
	char *res;
	int	fb;
	(void)ac;
	(void)av;

	if (ac > 1)
	{
		a = open(av[1], O_RDONLY);
		i = 0;
		res = NULL;
		fb = 0;
		while (res != NULL || fb == 0)
		{
			res = get_next_line(a);
			dprintf(FD, "\n!=====!\n\n");
			printf("Ligne%3d ===== %s", i, res);
			if (res != NULL)
				free (res);
			i++;
			fb = 1;
		}
		close(a);
	}
	return (EXIT_SUCCESS);	
}

// gcc -D BUFFER_SIZE=150 -D FD=-1 get_next_line.c && ./a.out file.txt | cat -e
// gcc -D BUFFER_SIZE=4096 -D FD=1 get_next_line.c && valgrind ./a.out file.txt --leak-check=full
