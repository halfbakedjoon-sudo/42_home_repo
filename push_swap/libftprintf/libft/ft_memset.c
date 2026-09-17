/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 15:30:54 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:19:30 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*temp;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	temp = (char *)s;
	while (index < n)
		temp[index++] = c;
	return (s);
}

//#include <stdio.h>
//int main(int argc, char **argv)
//{
//	printf("%s", (char *)ft_memset(argv[argc - 1], ' ', 10));
//}
