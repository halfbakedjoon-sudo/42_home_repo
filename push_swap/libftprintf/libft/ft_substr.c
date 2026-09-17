/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 15:45:43 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	end;
	size_t			size;
	size_t			index;
	char			*out;

	end = 0;
	if (!s)
		return (NULL);
	end = ft_strlen(s);
	size = end - start;
	if (end < start)
		size = 0;
	if (size > len)
		size = len;
	out = (char *)malloc((size + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[size] = 0;
	index = 0;
	while (index < size && s[start])
		out[index++] = s[start++];
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int	main(int argc, char **argv)
//{
//	char *printme = ft_substr(argv[argc - 3],
//		atoi(argv[argc - 2]), atoi(argv[argc - 1]));
//	printf("%s", printme);
//	free(printme);
//}
