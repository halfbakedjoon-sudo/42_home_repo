/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 15:39:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:29:38 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_copied;

	if (!dest)
		return (ft_strlen(src));
	size_copied = 0;
	while (src[size_copied] && size_copied + 1 < size)
	{
		dest[size_copied] = src[size_copied];
		size_copied++;
	}
	if (size > 0)
		dest[size_copied] = 0;
	return (ft_strlen(src));
}

//#include <stdio.h>
//#include <bsd/string.h>
//int main(int argc, char **argv)
//{
//	const char *src = "BROCHACHP";
//	size_t size = 0;
//	printf("my: %zu, %s\n", ft_strlcpy(argv[argc - 1],
//		src, size), argv[argc - 1]);
//	printf("or: %zu, %s\n", strlcpy(argv[argc - 2],
//		src, size), argv[argc - 2]);
//}
