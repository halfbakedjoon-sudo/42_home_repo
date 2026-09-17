/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:21:50 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/28 15:46:53 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index_big;
	size_t	index_search;
	size_t	index_small;

	index_big = 0;
	if (!little[0])
		return ((char *)big);
	while (big[index_big] && index_big < len)
	{
		index_small = 0;
		index_search = index_big;
		while (little[index_small] && little[index_small] == big[index_search]
			&& index_search < len)
		{
			index_small++;
			index_search++;
		}
		if (!little[index_small])
			return ((char *)&big[index_big]);
		index_big++;
	}
	return (NULL);
}

//#include <stdio.h>
//#include <bsd/string.h>
//
//int main(int argc, char **argv)
//{
//	printf("my: %p\n", ft_strnstr(argv[argc - 2], argv[argc - 1], 10));
//	printf("my: %p\n", strnstr(argv[argc - 2], argv[argc - 1], 10));
//}
