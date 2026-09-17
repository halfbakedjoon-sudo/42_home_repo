/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 16:35:32 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/28 14:59:06 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = NULL;
	while (*s)
	{
		if (*s == (char)c)
			temp = (char *)s;
		s++;
	}
	if (!c)
		return ((char *)s);
	return (temp);
}

//#include <stdio.h>
//int	main(int argc, char **argv)
//{
//	printf("%p, %p", argv[argc - 2],
//		ft_strrchr(argv[argc - 2], argv[argc - 1][0]));
//}
