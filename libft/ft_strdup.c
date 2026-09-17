/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:25:57 by johiew            #+#    #+#             */
/*   Updated: 2026/07/29 12:45:45 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
