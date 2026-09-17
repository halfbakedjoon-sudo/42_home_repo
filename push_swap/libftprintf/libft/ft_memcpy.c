/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 14:28:52 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:06:31 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tsrc;
	unsigned char	*tdest;
	size_t			index;

	if (!src || !dest || !n)
		return (dest);
	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	index = -1;
	while (++index < n)
		tdest[index] = tsrc[index];
	return (dest);
}

//#include <stdio.h>
//#include <string.h>
//int main(int argc, char **argv)
//{
//	char	*dest1 = argv[argc - 1];
////	char	*src1 = argv[argc - 1] + 10;
//	char	*dest2 = argv[argc - 2];
//	char	*src2 = argv[argc - 2] + 10;
//	ft_memcpy(dest1, NULL, 10);
//	memcpy(dest2, src2, 10);
//	printf("my: %s\n", argv[argc - 1]);
//	printf("or: %s", argv[argc - 2]);
////	printf("%zu\n", (size_t)-1);
////	printf("%ld\n", (long)18446744073709551615);
//}
