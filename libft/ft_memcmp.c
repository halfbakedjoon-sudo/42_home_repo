/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:04:46 by johiew            #+#    #+#             */
/*   Updated: 2026/07/28 15:04:46 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;
	size_t			index;

	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	index = 0;
	while (index < n)
	{
		if (ptrs1[index] != ptrs2[index])
			return (ptrs1[index] - ptrs2[index]);
		index++;
	}
	return (0);
}
