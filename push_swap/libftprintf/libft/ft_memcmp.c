/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 16:35:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:48:55 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ts1;
	unsigned char	*ts2;
	size_t			index;

	if (!s1 && !s2)
		return (0);
	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	if (!ts1)
		return (-(*ts2));
	if (!ts2)
		return (*ts1);
	index = 0;
	while (index < n)
	{
		if (ts1[index] != ts2[index])
			break ;
		index++;
	}
	if (index == n)
		return (0);
	return (ts1[index] - ts2[index]);
}

//#include <stdio.h>
//int	main(int argc, char **argv)
//{
//	printf("%d", ft_memcmp(argv[argc - 2], argv[argc - 1], 5));
//}
