/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:04:09 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 09:35:46 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_int(va_list *ap, char *type, size_t *index, int *length)
{
	int		n;
	char	*output;

	(void) type;
	n = va_arg(*ap, int);
	output = ft_itoa(n);
	write(1, output, ft_strlen(output));
	(*length) += ft_strlen(output);
	*index += 1;
	free (output);
}
