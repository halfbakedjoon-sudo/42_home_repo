/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 17:42:05 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 11:34:28 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(unsigned long n, char	*base, int *length)
{
	size_t	base_len;

	base_len = ft_strlen (base);
	if (n >= base_len)
		ft_puthex(n / base_len, base, length);
	write (1, &base[n % base_len], 1);
	(*length)++;
}

void	ft_print_ptr(va_list *ap, char *type, size_t *index, int *length)
{
	void	*ptr;

	(void) type;
	ptr = va_arg(*ap, void *);
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		(*length) += 5;
	}
	else
	{
		write(1, "0x", 2);
		(*length) += 2;
		ft_puthex((unsigned long)ptr, "0123456789abcdef", length);
	}
	*index += 1;
}
