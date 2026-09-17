/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_convert_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:54:02 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/08 18:22:21 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void	override_flags(t_print *print)
{
	if (print->handle_minus)
		print->handle_zero = 0;
	if (print->handle_plus)
		print->handle_space = 0;
	if (print->handle_prec && ft_strchr("diuxX", print->conversion))
		print->handle_zero = 0;
}

static char	*put_flags(const char *str, t_print *print)
{
	char	*valid_flags;
	int		index;

	valid_flags = "#+-0 ";
	while (*str)
	{
		index = 0;
		while (valid_flags[index] && valid_flags[index] != *str)
			index++;
		if (!valid_flags[index])
			break ;
		else if (valid_flags[index] == '#')
			print->handle_hash = 1;
		else if (valid_flags[index] == '+')
			print->handle_plus = 1;
		else if (valid_flags[index] == '-')
			print->handle_minus = 1;
		else if (valid_flags[index] == '0')
			print->handle_zero = 1;
		else if (valid_flags[index] == ' ')
			print->handle_space = 1;
		str++;
	}
	return ((char *)str);
}

static char	*put_num(const char *str, int *width)
{
	*width = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	return ((char *)str);
}

char	*ft_handle_conv(const char *str, int *size,
	va_list args, t_handle *handled)
{
	t_print		print;
	const char	*first;

	ft_bzero(&print, sizeof(t_print));
	first = str;
	str++;
	str = put_flags(str, &print);
	str = put_num(str, &(print.width));
	if (*str == '.')
	{
		print.handle_prec = 1;
		str = put_num(++str, &(print.precision));
	}
	if (print.precision < 0)
		print.handle_prec = 0;
	print.conversion = *str;
	override_flags(&print);
	ft_convert(print, args, size, handled);
	if (*str)
		return ((char *)++str);
	return ((char *)str);
}
