/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 16:35:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:03:36 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			index;

	if (!s)
		return (NULL);
	temp = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (temp[index] == (unsigned char)c)
			return ((void *)&temp[index]);
		index++;
	}
	return (NULL);
}

//#include <stdio.h>
//int	main(int argc, char **argv)
//{
//	printf("%p, %p", argv[argc - 2],
//		ft_memchr(argv[argc - 2], argv[argc - 1][0], 5));
//}
