/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 12:48:13 by johiew            #+#    #+#             */
/*   Updated: 2026/07/29 13:30:03 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	index_arry;
	char	*arry;

	arry = malloc (ft_strlen(s1)+ ft_strlen(s2) + 1);
	if (!arry)
		return (NULL);
	index = 0;
	index_arry = 0;
	while (s1[index])
		arry[index_arry++] = s1[index++];
	index = 0;
	while (s2[index])
		arry[index_arry++] = s2[index++];
	arry[index_arry] = 0;
	return (arry);
}
