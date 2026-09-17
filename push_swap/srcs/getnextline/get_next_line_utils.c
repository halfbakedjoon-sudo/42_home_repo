/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:37:52 by johiew            #+#    #+#             */
/*   Updated: 2026/08/07 14:19:29 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char		*arry;
	size_t		len;
	size_t		n;

	len = ft_strlen(s);
	arry = malloc (len + 1);
	if (!arry)
		return (NULL);
	n = 0;
	while (s[n])
	{
		arry[n] = s[n];
		n++;
	}
	arry[n] = 0;
	return (arry);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	index_arry;
	char	*arry;

	arry = malloc (ft_strlen(s1)+ ft_strlen(s2) + 1);
	if (!arry)
		return (NULL);
	index = 0;
	index_arry = 0;
	while (s1[index])
		arry[index_arry++] = s1[index++];
	index = 0;
	while (s2[index])
		arry[index_arry++] = s2[index++];
	arry[index_arry] = 0;
	return (arry);
}

int	ft_strnewline(const char *s)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != '\n')
		n++;
	if (s[n] == '\n')
		n++;
	return (n);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}
