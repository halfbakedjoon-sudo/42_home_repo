/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:57:35 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/03 16:12:23 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		printed;
	int		handled;

	handled = 0;
	printed = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
			str = ft_handle_conv(str, &printed, args, handled++);
		else
		{
			ft_putchar_fd(*str, 1);
			str++;
			printed++;
		}
	}
	va_end(args);
	return (printed);
}
