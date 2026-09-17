/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:50:42 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	if (!s)
		return (-2);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s && *(s++) != c)
		size++;
	return (size);
}

static char	*get_word(const char *s, char c)
{
	char	*out;
	int		index;

	index = 0;
	out = (char *)malloc((word_len(s, c) + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (*s && *s != c)
		out[index++] = *(s++);
	out[index] = 0;
	return (out);
}

static char	**free_all(char **out)
{
	int	out_index;

	out_index = 0;
	while (out[out_index])
		free(out[out_index++]);
	free(out);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**out;
	int		out_index;
	int		size;

	size = count_words(s, c);
	out = (char **)malloc((size + 1) * sizeof(char *));
	if (!s || !out)
		return (NULL);
	out_index = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			out[out_index] = get_word(s, c);
			if (!out[out_index++])
				return (free_all(out));
		}
		while (*s && *s != c)
			s++;
	}
	out[out_index] = 0;
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int	main(int argc, char **argv)
//{
//	int index = 0;
//	char **printme = ft_split(argv[argc - 2],
//		argv[argc - 1][0]);
//	if (!printme)
//		return (0);
//	while (printme[index])
//	{
//		printf("%s\n", printme[index]);
//		free(printme[index++]);
//	}
//	free(printme);
//}
