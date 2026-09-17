/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/04 18:49:34 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_c(int c, int *size)
{
	ft_putchar_fd(c, 1);
	(*size)++;
}

void	print_s(const char *str, int *size)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		*size += 6;
	}
	else
	{
		ft_putstr_fd((char *)str, 1);
		*size += ft_strlen(str);
	}
}

void	print_hex(unsigned long long i, int *size, int mode)
{
	if (i / 16 > 0)
		print_hex(i / 16, size, mode);
	i = i % 16;
	if (i < 10)
		ft_putchar_fd('0' + i, 1);
	else
	{
		i -= 10;
		if (mode)
			ft_putchar_fd('A' + i, 1);
		else
			ft_putchar_fd('a' + i, 1);
	}
	(*size)++;
}

void	print_p(void *p, int *size)
{
	if (!p)
	{
		ft_putstr_fd("(nil)", 1);
		(*size) += 5;
	}
	else
	{
		(*size) += 2;
		ft_putstr_fd("0x", 1);
		print_hex((unsigned long long)p, size, 0);
	}
}

void	print_x(unsigned int num, int *size, char conv)
{
	int	mode;

	mode = 0;
	if (conv == 'X')
		mode = 1;
	print_hex(num, size, mode);
}
