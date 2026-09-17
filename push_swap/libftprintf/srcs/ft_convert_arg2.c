/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:13:40 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/08 18:23:00 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_d(int num, int *size)
{
	ft_putnbr_fd(num, 1);
	(*size)++;
	if (num < 0)
		(*size)++;
	while (num / 10 != 0)
	{
		num /= 10;
		(*size)++;
	}
}

void	print_u(unsigned int num, int *size)
{
	if (num / 10 != 0)
		print_u(num / 10, size);
	(*size)++;
	ft_putchar_fd('0' + (num % 10), 1);
}

void	print_reg(char print, int *size, int handled)
{
	if (print || handled)
	{
		ft_putchar_fd('%', 1);
		(*size)++;
	}
	if (print)
	{
		ft_putchar_fd(print, 1);
		(*size)++;
	}
	if (!handled && !print)
		(*size) = -1;
}
