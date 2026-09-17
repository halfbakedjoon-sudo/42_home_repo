/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 15:33:51 by johiew            #+#    #+#             */
/*   Updated: 2026/07/31 09:32:08 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	n = 0;
	if (size <= len_dst)
		return (size + len_src);
	while (src[n] && len_dst + n < size - 1)
	{
		dst[len_dst + n] = src[n];
		n++;
	}
	dst[len_dst + n] = '\0';
	return (len_dst + len_src);
}
