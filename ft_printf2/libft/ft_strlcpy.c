/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 15:15:41 by johiew            #+#    #+#             */
/*   Updated: 2026/07/31 09:29:24 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	len;

	n = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[n] && n < size - 1)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = 0;
	return (len);
}
