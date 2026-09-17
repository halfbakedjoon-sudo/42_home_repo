/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 13:27:38 by johiew            #+#    #+#             */
/*   Updated: 2026/07/30 12:36:32 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arry;
	size_t	index_start_s1;
	size_t	index_end_s1;
	size_t	index_arry;

	index_start_s1 = 0;
	index_end_s1 = ft_strlen(s1);
	index_arry = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[index_start_s1] && is_in_set (s1[index_start_s1], set))
		index_start_s1++;
	while (index_end_s1 > index_start_s1
		&& is_in_set (s1[index_end_s1 - 1], set))
		index_end_s1--;
	arry = malloc (index_end_s1 - index_start_s1 + 1);
	if (!arry)
		return (NULL);
	while (index_start_s1 < index_end_s1)
		arry[index_arry++] = s1[index_start_s1++];
	arry[index_arry] = 0;
	return (arry);
}
