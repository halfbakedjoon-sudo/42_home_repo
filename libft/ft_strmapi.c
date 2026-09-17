/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 13:14:43 by johiew            #+#    #+#             */
/*   Updated: 2026/07/30 13:14:43 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*arry;
	unsigned int	index;

	if (!s || !f)
		return (NULL);
	arry = malloc (ft_strlen(s) + 1);
	if (!arry)
		return (NULL);
	index = 0;
	while (s[index])
	{
		arry[index] = f(index, s[index]);
		index++;
	}
	arry[index] = 0;
	return (arry);
}
