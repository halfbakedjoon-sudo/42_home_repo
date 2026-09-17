/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:33:37 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 09:35:54 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(va_list *ap, char *type, size_t *index, int *length)
{
	int	c;

	(void) type;
	c = va_arg(*ap, int);
	write (1, &c, 1);
	(*length)++;
	*index += 1;
}
