/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:17:30 by utenret           #+#    #+#             */
/*   Updated: 2022/11/30 15:17:59 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>

bool	are_null(char **strs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && strs[i] == NULL)
		++i;
	return (i == n || strs[i] == NULL);
}

void	free_strs(char **strs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		++i;
	}
}

int	main(int ac, char **av)
{
	char	**lines;
	int		*fds;
	int		i;

	if (ac > 1)
	{
// fds

		++av;
		--ac;
		fds = (int *)malloc(ac * sizeof(int));
		i = 0;
		while (i < ac)
		{
			fds[i] = open(av[i], O_RDONLY);
			printf("FDP ======%d\n", fds[i]);
			++i;
		}
//
// lines

		lines = (char **)malloc(ac * sizeof(char *));
		i = 0;
		while (i < ac)
		{
			lines[i] = get_next_line(fds[i]);
			printf("FD[%d] --> [%s]\n", i, lines[i]);
			++i;
		}
		while (are_null(lines, ac) == false)
		{
			free_strs(lines, ac);
			i = 0;
			while (i < ac)
			{
				if (lines[i] != NULL)
					lines[i] = get_next_line(fds[i]);
				printf("FD[%d] --> [%s]\n", i, lines[i]);
				++i;
			}
		}
//
// closing
		i = 0;
		while (i < ac)
		{
			free(lines[i]);
			close(fds[i]);
			++i;
		}
		free(lines);
		free(fds);
//
	}
	return (EXIT_SUCCESS);	
}
