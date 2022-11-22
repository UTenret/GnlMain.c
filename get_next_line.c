/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:44:03 by utenret           #+#    #+#             */
/*   Updated: 2022/11/22 16:01:53 by utenret          ###   ########.fr       */
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

char    **ft_split(char const *str, char c);
void    ft_cleanup(char **split);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_does_str_contains_n(char	*str);
char	*ft_strnjoin(char *s1, char *s2, int size);
/*
char	*ft_strdup(char *s)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (ptr != NULL)
		ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}
*/
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
//	dprintf(FD, "doyougetherethough\n");
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
	dprintf(FD, "size =========%d\n", size);
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
//	dprintf(FD, "doyougetherethough\n");
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
	dprintf(FD, "intresting dst -> %c\n", dst[i]);
	dprintf(FD, "intresting src -> %c\n", src[i]);
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

/*
char	*ft_gnl(char *gnl, char *res)
{
	int		l;	 

	l = ft_does_str_contains_n(gnl);
	dprintf(FD, "l ====== %d\n", l);
	res = malloc(sizeof(char) * l + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, gnl, l + 1);
//	gnl = ft_memset(gnl, 0, l);
	ft_strlcpy(gnl, gnl + l, ft_strlen(gnl));
	return (res);
}
*/
int	ft_does_str_contains_n(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (i + 1);
	dprintf(FD, "str ========%s\n", str);
	while(str[i])
	{
		i++;
		if (str[i] == '\n')
			return (i + 1);
	}
	return (-1);
}
/*
int	ft_where_nozero(char *str)
{
	size_t	i;

	i = 0;
	while(i == 0)
		i++;
	return (i);
}

void	ft_cani(char **gnl)
{



}
*/
char	*get_next_line(int fd)
{
	static	char	gnl[BUFFER_SIZE + 1] = {0};
	char	buf[BUFFER_SIZE + 1];
	char	*res;
	int	c;
	int	i;

	ft_memset(buf, 0, BUFFER_SIZE + 1);
	dprintf(FD, "GNL1 ===== %s\n", gnl);
	i = ft_does_str_contains_n(gnl);
	dprintf(FD, "THE I ====%d\n", i);
	res = NULL;
//	dprintf(FD, "i ========%d\n", i);
	if (i >= 0)
	{
		dprintf(FD, "here\n");
		dprintf(FD, "strlen de gnl beginning -> %zu\n", ft_strlen(gnl));
		c = ft_strlen(gnl);
		dprintf(FD, "c =====%d\n", c);
		if (i < ft_strlen(gnl))	
		{
			dprintf(FD, "haaaaaar\n");
			res = ft_strnjoin(res, gnl, i);
			ft_strlcpy(gnl, gnl + i, BUFFER_SIZE + 1);	
			dprintf(FD, "c2 =====%d\n", c);
//			dprintf(FD, "strlen de gnl after -> %zu\n", ft_strlen(gnl));
			ft_memset(gnl + /*ft_strlen(gnl)*/c, 0, BUFFER_SIZE + 1 - c);//ft_strlen(gnl));
	//		res = ft_strjoin(res, buf);
//			ft_strlcpy(res, gnl, i);	
//			ft_strlcpy(gnl, gnl + i, BUFFER_SIZE);	
	//		ft_memset(gnl, 0, i + ft_where_nozero(gnl));
			dprintf(FD, "strlen de gnl after memest -> %zu\n", ft_strlen(gnl));
			dprintf(FD, "GNL ===== %s\n", gnl);
			dprintf(FD, "haaaaahgjghjghjhgar\n");
			return (res);	
		}
		else
		{ 
			res = ft_strjoin(res, gnl);
			ft_memset(gnl, 0, BUFFER_SIZE);
			dprintf(FD, "cock\n");
			return (res);
		}
	//	dprintf(FD, "catchme bitch\n");
	//	return (ft_gnl(gnl, res));		
	}
	//	dprintf(FD, "here2\n");
//	if (ft_does_str_contains_n(buf) == -1)
//		c = read(fd, buf, BUFFER_SIZE);
	else
	{
		dprintf(FD, "here20\n");
		i = ft_does_str_contains_n(buf);	
		dprintf(FD, "THE I2 ====%d\n", i);
		res = NULL;
		res = ft_strjoin(res, gnl);	
		dprintf(FD, "GNL4 ===== %s\n", gnl);
		ft_memset(gnl, 0, BUFFER_SIZE);
		dprintf(FD, "GNL5 ===== %s\n", gnl);
		while (i == -1)
		{
			c = read(fd, buf, BUFFER_SIZE);
			dprintf(FD, "buf99 ====== %s\n", buf);
			i = ft_does_str_contains_n(buf); // need to fix that
			dprintf(FD, "here3\n");
			dprintf(FD, "i ========%d\n", i);
	//		dprintf(FD, "i ==%d\n", i);
	//		dprintf(FD, "strlen buf =====%zu\n", ft_strlen(buf));
	//		dprintf(FD, "buf2 ==========%s-\n", buf);
	//		dprintf(FD, "result =====%i\n", ft_does_str_contains_n(buf));
			if (c == 0)
				return (NULL);
			if (i == -1)
			{
				dprintf(FD, "here30\n");
				res = ft_strjoin(res, buf);	
				ft_memset(buf, 0, BUFFER_SIZE);
			}
//			if (c == -1)
//				return (NULL);
		}
		if (i == 0)
			return (res);
		else
		{
			dprintf(FD, "here5\n");
	//		dprintf(FD, "buf ==========%s-\n", buf);
			ft_strlcpy(gnl, buf + i, c + 1 - i);	
//			dprintf(FD, "GNL ==========%s-\n", gnl);
			ft_memset(buf + i, 0, c - i);
			res = ft_strjoin(res, buf);
			ft_memset(buf, 0, BUFFER_SIZE);
//			ft_strlcpy(gnl, gnl + i, ft_strlen(gnl));
	//		buf[ft_does_str_contains_n(buf)] = '\0';
//			dprintf(FD, "here6\n");
		//	dprintf(FD, "here7\n");
			return(res);	
	//		dprintf(FD, "here8\n");
		}
//	dprintf(FD, "tauluwq ========%d\n", i);
	}
//	dprintf(FD, "i ========%d\n", i);
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
			if (res)
				free (res);
			i++;
			fb = 1;
		}
	}
	return (EXIT_SUCCESS);	
}

// gcc -D BUFFER_SIZE=150 -D FD=-1 get_next_line.c && ./a.out file.txt | cat -e
