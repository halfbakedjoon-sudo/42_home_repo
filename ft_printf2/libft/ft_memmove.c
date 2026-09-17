/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 13:50:04 by johiew            #+#    #+#             */
/*   Updated: 2026/07/27 14:51:52 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrsrc;
	unsigned char	*ptrdest;
	size_t			i;

	ptrsrc = (unsigned char *)src;
	ptrdest = (unsigned char *)dest;
	i = 0;
	if (ptrdest > ptrsrc && ptrdest < ptrsrc + n)
	{
		i = n;
		while (i > 0)
		{
			ptrdest[i - 1] = ptrsrc[i - 1];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			ptrdest[i] = ptrsrc[i];
			i++;
		}
	}
	return (dest);
}
