/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:38:05 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void	set_signd(int num, int *sign, unsigned int *d)
{
	*d = num;
	*sign = 1;
	if (num < 0)
	{
		*sign = -1;
		*d = -num;
	}
}

static void	print_unsigned(unsigned int num, int fd)
{
	if (num < 0)
		ft_putchar_fd('-', fd);
	if (num / 10 != 0)
		print_unsigned(num / 10, fd);
	ft_putchar_fd('0' + (num % 10), fd);
}

void	print_d(t_print print, int num, int *size, int fd)
{
	int				tsize;
	int				zeros;
	int				sign;
	unsigned int	d;

	set_signd(num, &sign, &d);
	tsize = get_numconvsize(&zeros, print, d, sign);
	if (!print.handle_minus && !print.handle_zero)
		print_spaces(&tsize, print.width, fd);
	if (!print.handle_prec || (print.handle_prec && (print.precision > 0
				|| (print.precision == 0 && num != 0))))
	{
		print_spaceplus(print, num, fd);
		if (print.handle_prec || print.handle_zero)
			while (zeros-- > 0)
				ft_putchar_fd('0', fd);
		print_unsigned(d, fd);
	}
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	*size += tsize;
}

void	print_u(t_print print, unsigned int num, int *size, int fd)
{
	int	tsize;
	int	zeros;

	tsize = get_numconvsize(&zeros, print, num, 1);
	if (!print.handle_minus && !print.handle_zero)
		print_spaces(&tsize, print.width, fd);
	if (!print.handle_prec || (print.handle_prec && (print.precision > 0
				|| (print.precision == 0 && num != 0))))
	{
		if (print.handle_prec || print.handle_zero)
			while (zeros-- > 0)
				ft_putchar_fd('0', fd);
		print_unsigned(num, fd);
	}
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	*size += tsize;
}

void	print_reg(t_print print, int *size, int handled, int fd)
{
	if (print.conversion || handled)
	{
		ft_putchar_fd('%', fd);
		(*size)++;
	}
	if (print.conversion)
	{
		ft_putchar_fd(print.conversion, fd);
		(*size)++;
	}
	if (!handled && !print.conversion)
		(*size) = -1;
}
