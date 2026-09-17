/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 09:52:03 by johiew            #+#    #+#             */
/*   Updated: 2026/07/29 12:45:01 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arry;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	arry = malloc (nmemb * size);
	if (!arry)
		return (NULL);
	ft_bzero(arry, nmemb * size);
	return (arry);
}
