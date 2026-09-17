/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:35:41 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

void	ft_convert(t_print print, va_list args, int *size, t_handle *handled)
{
	if (print.conversion == 'c')
		print_c(print, va_arg(args, int), size, handled->fd);
	else if (print.conversion == 's')
		print_s(print, va_arg(args, const char *), size, handled->fd);
	else if (print.conversion == 'p')
		print_p(print, va_arg(args, void *), size, handled->fd);
	else if (print.conversion == 'i' || print.conversion == 'd')
		print_d(print, va_arg(args, int), size, handled->fd);
	else if (print.conversion == 'u')
		print_u(print, va_arg(args, unsigned int), size, handled->fd);
	else if (print.conversion == 'x' || print.conversion == 'X')
		print_x(print, va_arg(args, unsigned int), size, handled->fd);
	else if (print.conversion == '%')
		print_c(print, '%', size, handled->fd);
	else
		print_reg(print, size, handled->handled, handled->fd);
}
