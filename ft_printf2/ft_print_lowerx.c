/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lowerx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:28:10 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 09:35:41 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int n, int *length)
{
	if (n >= 16)
		ft_putnbr_unsigned(n / 16, length);
	write(1, &"0123456789abcdef"[n % 16], 1);
	(*length)++;
}

void	ft_print_lowerx(va_list *ap, char *type, size_t *index, int *length)
{
	unsigned int	n;

	(void) type;
	n = va_arg(*ap, unsigned int);
	ft_putnbr_unsigned(n, length);
	*index += 1;
}
