/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 14:28:52 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 18:25:06 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tsrc;
	unsigned char	*tdest;
	size_t			index;

	if (!src || !dest || !n)
		return (dest);
	if (dest - src <= 0)
		return (ft_memcpy(dest, src, n));
	tsrc = (unsigned char *)src;
	tdest = (unsigned char *)dest;
	index = n;
	while (index-- > 0)
		tdest[index] = tsrc[index];
	return (dest);
}

//#include <stdio.h>
//#include <string.h>
//int main(int argc, char **argv)
//{
//	char	*dest1 = argv[argc - 4] + 1;
//	char	*src1 = argv[argc - 3];
//	char	*dest2 = argv[argc - 2] + 1;
//	char	*src2 = argv[argc - 1];
//	ft_memmove(src1, dest1, 8);
//	memmove(src2, dest2, 8);
//	printf("dest:%p\nsrc: %p\nmy: %s\n", dest1, src1, argv[argc - 3]);
//	printf("dest:%p\nsrc: %p\nor: %s", dest2, src2, argv[argc - 1]);
////	printf("%zu\n", (size_t)-1);
////	printf("%ld\n", (long)18446744073709551615);
//}
