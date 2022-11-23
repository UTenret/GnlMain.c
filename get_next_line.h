/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:26:02 by utenret           #+#    #+#             */
/*   Updated: 2022/11/23 16:27:29 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE__H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

char		*ft_strjoin(char *s1, char *s2);
char		*ft_strnjoin(char *s1, char *s2, int size);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		*ft_memset(void *s, int c, size_t n);

int			ft_does_str_contains_n(char	*str);
static char	*ft_rest(char *res, char *gnl, int i);
static char	*ft_weout(char **res, char *buf, char *gnl, int c);
static int	ft_letsread(char **res, char *buf, char *gnl, int fd);
char		*get_next_line(int fd);

#endif
