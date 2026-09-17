/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:57:35 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/03 17:08:21 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

int	ft_printf(int fd, const char *str, ...)
{
	va_list		args;
	t_handle	handled;
	int			printed;

	handled.handled = 0;
	handled.fd = fd;
	printed = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str = ft_handle_conv(str, &printed, args, &handled);
			(handled.handled)++;
		}
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
			printed++;
		}
	}
	va_end(args);
	return (printed);
}
