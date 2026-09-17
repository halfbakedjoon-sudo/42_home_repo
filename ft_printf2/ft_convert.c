/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 13:33:43 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 09:35:59 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert(va_list *ap, char *type, size_t *index, int *length)
{
	if (*type == '%')
		ft_print_perc(ap, type, index, length);
	if (*type == 'c')
		ft_print_char(ap, type, index, length);
	if (*type == 's')
		ft_print_str(ap, type, index, length);
	if (*type == 'p')
		ft_print_ptr(ap, type, index, length);
	if (*type == 'i' || *type == 'd')
		ft_print_int(ap, type, index, length);
	if (*type == 'u')
		ft_print_u(ap, type, index, length);
	if (*type == 'x')
		ft_print_lowerx(ap, type, index, length);
	if (*type == 'X')
		ft_print_upperx(ap, type, index, length);
}
