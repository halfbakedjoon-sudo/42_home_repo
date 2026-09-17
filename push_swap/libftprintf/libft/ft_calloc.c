/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:52:12 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/31 16:14:58 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*temp;
	char	*setter;
	size_t	index;

	if ((nmemb > 2147483647 || size > 2147483647)
		|| nmemb * size > 2147483647)
	{
		if (nmemb != 0 && size != 0)
			return (NULL);
	}
	temp = (void *)malloc(nmemb * size);
	if (!temp)
		return (NULL);
	setter = (char *)temp;
	index = 0;
	while (index < nmemb * size)
		setter[index++] = 0;
	return (temp);
}

//int	main()
//{
//	char *test = (char *)ft_calloc(5, 1);
//	free(test);
//}
