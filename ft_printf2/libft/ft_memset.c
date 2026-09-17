/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 10:49:04 by johiew            #+#    #+#             */
/*   Updated: 2026/07/27 12:36:15 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	unsigned char	*ptr;
	size_t			n;

	ptr = (unsigned char *)s;
	n = 0;
	while (n < size)
	{
		ptr[n] = (unsigned char)c;
		n++;
	}
	return (s);
}
