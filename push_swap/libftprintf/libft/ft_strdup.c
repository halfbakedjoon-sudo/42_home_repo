/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 18:04:15 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:53:57 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp;
	size_t	size;
	size_t	index;

	if (!s)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	temp = (char *)malloc((size + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	temp[size] = 0;
	index = 0;
	while (index < size)
	{
		temp[index] = s[index];
		index++;
	}
	return (temp);
}
//int	main()
//{
//	char *test = ft_strdup("hello");
//	free(test);
//}
