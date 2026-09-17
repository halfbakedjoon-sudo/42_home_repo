/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:41:01 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_back(const char *s1, const char *set)
{
	int	set_index;
	int	s1_index;
	int	out_index;
	int	size;

	size = 0;
	s1_index = ft_strlen(s1) - 1;
	out_index = 0;
	while (s1_index >= 0)
	{
		set_index = 0;
		while (set[set_index] && set[set_index] != s1[s1_index])
			set_index++;
		if (set[set_index])
			size++;
		else
			break ;
		s1_index--;
	}
	return (size);
}

static int	count_front(const char *s1, const char *set)
{
	int	set_index;
	int	s1_index;
	int	out_index;
	int	size;

	size = 0;
	s1_index = 0;
	out_index = 0;
	while (s1[s1_index])
	{
		set_index = 0;
		while (set[set_index] && set[set_index] != s1[s1_index])
			set_index++;
		if (set[set_index])
			size++;
		else
			break ;
		s1_index++;
	}
	return (size);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		front_trim;
	int		back_trim;
	int		size;
	int		index;
	char	*out;

	front_trim = count_front(s1, set);
	back_trim = count_back(s1, set);
	size = ft_strlen(s1) - front_trim - back_trim;
	if (size <= 0)
		size = 0;
	out = (char *)malloc((size + 1) * sizeof(char));
	if (!out)
		return (NULL);
	index = 0;
	while (index < size)
		out[index++] = s1[front_trim++];
	out[size] = 0;
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int	main(int argc, char **argv)
//{
//	char *printme = ft_strtrim(argv[argc - 2],
//		argv[argc - 1]);
//	printf("%s", printme);
//	free(printme);
//}
