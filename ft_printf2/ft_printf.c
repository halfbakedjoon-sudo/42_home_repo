/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:45:47 by johiew            #+#    #+#             */
/*   Updated: 2026/08/07 10:25:23 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_identifier(char	*type)
{
	char	*check;
	int		n;

	check = "cspdiuxX%";
	n = 0;
	while (check[n])
	{
		if (*type == check[n])
			return (1);
		n++;
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	size_t	n;
	va_list	ap;
	int		length;

	n = 0;
	length = 0;
	va_start(ap, s);
	while (s[n])
	{
		if (s[n] != '%')
		{
			write (1, &s[n++], 1);
			length++;
		}
		else
		{
			n++;
			if (is_identifier((char *)s + n))
				ft_convert(&ap, (char *)s + n, &n, &length);
		}
	}
	va_end (ap);
	return (length);
}
/*#include <stdio.h>
int	main(void)
{
	char	*s;
	int		ret1;
	int		ret2;

	s = NULL;

	ret1 = printf("%%, %c, %s, %p, %d, %i, %u, %x, %X\n",
			'A', (char *)NULL, s, 123, 123, -1, 2147483647, 2147483647);

	printf("printf return: %d\n", ret1);

	ret2 = ft_printf("%%, %c, %s, %p, %d, %i, %u, %x, %X\n",
			'A', (char *)NULL, s, 123, 123, -1, 2147483647, 2147483647);

	printf("ft_printf return: %d\n", ret2);

	return (0);
}*/
