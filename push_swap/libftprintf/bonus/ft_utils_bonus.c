/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:34:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:20:47 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

int	count_base(unsigned long long num, unsigned long long base)
{
	int	size;

	size = 1;
	while (num / base != 0)
	{
		num /= base;
		size++;
	}
	return (size);
}

int	get_numconvsize(int *zeros, t_print print, unsigned int num, int sign)
{
	int	base;
	int	tsize;

	if (print.handle_prec && print.precision == 0 && num == 0)
		return (0);
	if (ft_toupper(print.conversion) == 'X')
		base = 16;
	else
		base = 10;
	*zeros = 0;
	tsize = count_base(num, base);
	if (print.handle_prec && print.precision > tsize)
		*zeros = print.precision - tsize;
	if (!(print.conversion == 'u' || ft_toupper(print.conversion) == 'X'))
	{
		if (sign == -1 || print.handle_plus || print.handle_space)
			tsize++;
	}
	if (ft_toupper(print.conversion) == 'X' && num > 0)
		tsize += 2 * (print.handle_hash);
	if (print.handle_zero && print.width > tsize)
		*zeros = print.width - tsize;
	tsize += *zeros;
	return (tsize);
}

void	print_spaceplus(t_print print, int num, int fd)
{
	if (num < 0)
		ft_putchar_fd('-', fd);
	if (num >= 0)
	{
		if (print.handle_space)
			ft_putchar_fd(' ', fd);
		else if (print.handle_plus)
			ft_putchar_fd('+', fd);
	}
}

void	print_spaces(int *tsize, int width, int fd)
{
	while (*tsize < width)
	{
		ft_putchar_fd(' ', fd);
		(*tsize)++;
	}
}
