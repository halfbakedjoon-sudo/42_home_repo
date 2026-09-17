/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 14:23:45 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	index;
	char	*out;

	size = ft_strlen(s);
	out = (char *)malloc((size + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[size] = 0;
	index = 0;
	while (index < size)
	{
		out[index] = f(index, s[index]);
		index++;
	}
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//char	test(unsigned int n, char c)
//{
//	printf("%c\n", c);
//	return (c + (n % 2));
//}
//
//int	main(int argc, char **argv)
//{
//	char *printme = ft_strmapi(argv[argc - 1], &test);
//	printf("%s", printme);
//	free(printme);
//}
