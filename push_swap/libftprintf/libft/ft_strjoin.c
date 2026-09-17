/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:56:27 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*out;
	size_t	index;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	index = 0;
	while (*s1)
		out[index++] = *s1++;
	while (*s2)
		out[index++] = *s2++;
	out[index] = 0;
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int	main(int argc, char **argv)
//{
//	char *printme = ft_strjoin(argv[argc - 2],
//		argv[argc - 1]);
//	printf("%s", printme);
//	free(printme);
//}
