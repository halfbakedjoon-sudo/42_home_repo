/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:12:12 by johiew            #+#    #+#             */
/*   Updated: 2026/07/31 09:19:04 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	n;
	int	count;

	n = 0;
	count = 0;
	while (s[n])
	{
		while (s[n] == c)
			n++;
		if (s[n])
			count++;
		while (s[n] && s[n] != c)
			n++;
	}
	return (count);
}

static void	free_split(char **arry, int count)
{
	while (count--)
		free(arry[count]);
	free(arry);
}

static int	add_word(char **arr, char const *s, char c, int *i)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	arr[*i] = ft_substr(s, 0, len);
	if (!arr[*i])
		return (0);
	(*i)++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = add_word(arr, s, c, &i);
		if (!len)
			return (free_split(arr, i), NULL);
		s += len;
	}
	arr[i] = NULL;
	return (arr);
}

/*int	main(void)
{
	char	*input = " I am not so noob. what you want is it ";
	char	**result = ft_split (input, ' ');
	int	n = 0;
	int	j = 0;
	while (result[n])
	{
		j = 0;
		while (result[n][j])
		{
			write (1, &result[n][j], 1);
			j++;
		}
		write (1, "\n", 1);
		n++;
	}
	n = 0;
	while (result[n])
	{
		free (result[n]);
		n++;
	}
	free (result);
	return (0);
}*/
