/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 16:35:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:31:04 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (s1[index])
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index] || index == n)
			break ;
		index++;
	}
	if (index == n)
		return (0);
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

//#include <stdio.h>
//#include <string.h>
//int	main(int argc, char **argv)
//{
//	int	size = 5;
//	argv[argc - 2][3] = -42;
//	printf("my: %d\n", ft_strncmp(argv[argc - 2], argv[argc - 1], size));
//	printf("or: %d", strncmp(argv[argc - 2], argv[argc - 1], size));
//}
