/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:35:01 by johiew            #+#    #+#             */
/*   Updated: 2026/08/10 10:26:27 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	char		*tmp;
	char		*tmp2;
	size_t		n;

	n = 0;
	if (fd < 0)
		return (NULL);
	stash = ft_read (stash, buffer, fd);
	if (!check_stash(&stash))
		return (NULL);
	n = ft_strnewline(stash);
	tmp2 = malloc (n + 1);
	n = ft_put_line (stash, tmp2);
	tmp = ft_strdup(stash + n);
	free (stash);
	stash = tmp;
	return (tmp2);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	i = 0;
	//line = get_next_line(fd);
	//printf("Line %d: %s", i, line);
	//free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", i, line);
		free(line);
		i++;
	}
	printf("--- EOF (%d lines) ---\n", i);
	close(fd);
	return (0);
}*/
