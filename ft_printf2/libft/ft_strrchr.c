/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:05:19 by johiew            #+#    #+#             */
/*   Updated: 2026/07/28 11:05:19 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int		n;
	char	*l;

	n = 0;
	l = NULL;
	while (s[n])
	{
		if (s[n] == (char)c)
			l = (char *)(s + n);
		n++;
	}
	if (s[n] == (char)c)
		l = (char *)(s + n);
	return (l);
}
