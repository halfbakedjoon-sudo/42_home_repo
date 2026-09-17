/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:37:16 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

void	print_c(t_print print, int c, int *size, int fd)
{
	int	tsize;

	tsize = 1;
	if (!print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	ft_putchar_fd(c, fd);
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	(*size) += tsize;
}

void	print_s(t_print print, const char *str, int *size, int fd)
{
	int	tsize;
	int	psize;

	tsize = 0;
	if (!str)
	{
		if (!print.handle_prec || (print.handle_prec && print.precision >= 6))
			tsize = 6;
	}
	else
		tsize = ft_strlen(str);
	if (print.handle_prec && tsize > print.precision)
		tsize = print.precision;
	psize = tsize;
	if (!print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	if (str)
		while (psize--)
			ft_putchar_fd(*(str++), fd);
	else if (!print.handle_prec || (print.handle_prec && print.precision >= 6))
		ft_putstr_fd("(null)", fd);
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	(*size) += tsize;
}

void	print_hex(unsigned long long i, int mode, int fd)
{
	if (i / 16 > 0)
		print_hex(i / 16, mode, fd);
	i = i % 16;
	if (i < 10)
		ft_putchar_fd('0' + i, fd);
	else
	{
		i -= 10;
		if (mode)
			ft_putchar_fd('A' + i, fd);
		else
			ft_putchar_fd('a' + i, fd);
	}
}

void	print_p(t_print print, void *p, int *size, int fd)
{
	int	tsize;

	if (!p)
		tsize = 5;
	else
		tsize = 2 + count_base((unsigned long long)p, 16)
			+ (print.handle_plus || print.handle_space);
	if (!print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	if (!p)
		ft_putstr_fd("(nil)", fd);
	else
	{
		if (print.handle_plus)
			ft_putchar_fd('+', fd);
		else if (print.handle_space)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd("0x", fd);
		print_hex((unsigned long long)p, 0, fd);
	}
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	*size += tsize;
}

void	print_x(t_print print, unsigned int num, int *size, int fd)
{
	int	mode;
	int	tsize;
	int	zeros;

	tsize = get_numconvsize(&zeros, print, num, 1);
	mode = 0;
	if (print.conversion == 'X')
		mode = 1;
	if (!print.handle_minus && !print.handle_zero)
		print_spaces(&tsize, print.width, fd);
	if (!print.handle_prec || (print.handle_prec && (print.precision > 0
				|| (print.precision == 0 && num != 0))))
	{
		if (print.handle_hash && mode && num > 0)
			ft_putstr_fd("0X", fd);
		else if (print.handle_hash && num > 0)
			ft_putstr_fd("0x", fd);
		if (print.handle_prec || print.handle_zero)
			while (zeros-- > 0)
				ft_putchar_fd('0', fd);
		print_hex(num, mode, fd);
	}
	if (print.handle_minus)
		print_spaces(&tsize, print.width, fd);
	*size += tsize;
}
