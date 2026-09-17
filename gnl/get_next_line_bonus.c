/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:35:01 by johiew            #+#    #+#             */
/*   Updated: 2026/08/10 10:26:57 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *stash, char *buffer, int fd)
{
	ssize_t	bytes;
	char	*tmp;

	if (stash == NULL || !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0 && stash == NULL)
			return (NULL);
		while (bytes > 0)
		{
			buffer[bytes] = 0;
			if (stash == NULL)
				tmp = ft_strdup(buffer);
			else
			{
				tmp = ft_strjoin(stash, buffer);
				free(stash);
			}
			stash = tmp;
			if (ft_strchr(stash, '\n'))
				break ;
			bytes = read(fd, buffer, BUFFER_SIZE);
		}
	}
	return (stash);
}

int	check_stash(char **stash)
{
	if (*stash == NULL || (*stash)[0] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (0);
	}
	return (1);
}

size_t	ft_put_line(char *stash, char *tmp2)
{
	size_t	n;

	n = 0;
	while (stash[n] && stash[n] != '\n')
	{
		tmp2[n] = stash[n];
		n++;
	}
	if (stash[n] == '\n')
	{
		tmp2[n] = '\n';
		n++;
	}
	tmp2[n] = '\0';
	return (n);
}

char	*get_next_line_bonus(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash[1048576];
	char		*tmp;
	char		*tmp2;
	size_t		n;

	n = 0;
	if (fd < 0)
		return (NULL);
	stash[fd] = ft_read (stash[fd], buffer, fd);
	if (!check_stash(&stash[fd]))
		return (NULL);
	n = ft_strnewline(stash[fd]);
	tmp2 = malloc (n + 1);
	n = ft_put_line (stash[fd], tmp2);
	tmp = ft_strdup(stash[fd] + n);
	free (stash[fd]);
	stash[fd] = tmp;
	return (tmp2);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd[2000];
	char	*line;
	int		n;
	int		total_file;
	int		i;

	n = 0;
	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	while (n < argc)
	{
		fd[n] = open(argv[n], O_RDONLY);
		n++;
	}
	total_file = n;
	n = 1;
	while (n < argc)
	{
		if (fd[n] < 0)
		{
			printf("Error opening file %d\n", n);
			return (1);
		}
		n++;
	}
	n = 1;
	while (n < total_file)
	{
		i = 0;
		while ((line = get_next_line_bonus(fd[n])) != NULL)
		{
			printf("Line %d: %s", i, line);
			free(line);
			i++;
		}
		printf("--- EOF (%d lines) ---\n", i);
		n++;
	}
	n = 0;
	while (n < argc)
	{
		close (fd[n]);
		n++;
	}
	return (0);
}*/
