/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 15:39:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:28:55 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_src;
	size_t	index_src;
	size_t	size_dest;
	size_t	index_dest;

	size_src = 0;
	size_dest = 0;
	while (src[size_src])
		size_src++;
	if (!dest)
		return (size + size_src);
	while (dest[size_dest])
		size_dest++;
	if (size_dest + 1 > size)
		return (size + size_src);
	index_src = 0;
	index_dest = size_dest;
	while (src[index_src] && index_dest + 1 < size)
	{
		dest[index_dest] = src[index_src];
		index_dest++;
		index_src++;
	}
	dest[index_dest] = 0;
	return (size_dest + size_src);
}

//#include <stdio.h>
//#include <bsd/string.h>
//int main(int argc, char **argv)
//{
//	const char *src = "lorem ipsum dolor sit amet";
//	size_t size = 5;
//	ft_memset(argv[argc - 1], 'r', 15);
//	ft_memset(argv[argc - 2], 'r', 15);
//	printf("my: %zu, %s\n", ft_strlcat(argv[argc - 1],
//		src, size), argv[argc - 1]);
//	printf("or: %zu, %s\n", strlcat(argv[argc - 2],
//		src, size), argv[argc - 2]);
//}
