/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/03 16:18:43 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_convert(char print, va_list args, int handled, int *size)
{
	if (print == 'c')
		print_c(va_arg(args, int), size);
	else if (print == 's')
		print_s(va_arg(args, const char *), size);
	else if (print == 'p')
		print_p(va_arg(args, void *), size);
	else if (print == 'i' || print == 'd')
		print_d(va_arg(args, int), size);
	else if (print == 'u')
		print_u(va_arg(args, unsigned int), size);
	else if (print == 'x' || print == 'X')
		print_x(va_arg(args, unsigned int), size, print);
	else if (print == '%')
		print_c('%', size);
	else
		print_reg(print, size, handled);
}
