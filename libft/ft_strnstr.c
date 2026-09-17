/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:17:19 by johiew            #+#    #+#             */
/*   Updated: 2026/07/28 15:17:19 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	bigindex;
	size_t	litindex;
	size_t	n;

	bigindex = 0;
	litindex = 0;
	n = 0;
	if (little[litindex] == 0)
		return ((void *)big);
	while (n < len && big[bigindex + n])
	{
		litindex = 0;
		bigindex = 0;
		while ((bigindex + n) < len
			&& little[litindex]
			&& big[bigindex + n] == little[litindex])
		{
			bigindex++;
			litindex++;
		}
		if (little[litindex] == 0)
			return ((void *)big + n);
		n++;
	}
	return (NULL);
}
