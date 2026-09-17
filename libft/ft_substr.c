/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:45:10 by johiew            #+#    #+#             */
/*   Updated: 2026/07/29 12:47:02 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_empty_str(void)
{
	char	*arry;

	arry = malloc(1);
	if (!arry)
		return (NULL);
	arry[0] = '\0';
	return (arry);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arry;
	size_t	index;
	size_t	aclen;

	index = 0;
	if (start >= ft_strlen(s))
		return (ft_empty_str());
	aclen = ft_strlen(s) - start;
	if (aclen > len)
		aclen = len;
	arry = malloc(aclen + 1);
	if (!arry)
		return (NULL);
	while (index < aclen)
	{
		arry[index] = s[start + index];
		index++;
	}
	arry[index] = '\0';
	return (arry);
}
