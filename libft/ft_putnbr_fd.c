/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:30:17 by johiew            #+#    #+#             */
/*   Updated: 2026/07/30 16:30:17 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	input;
	char	output;

	input = (long)n;
	if (input < 0)
	{
		write (fd, "-", 1);
		input = -input;
	}
	if (input >= 10)
		ft_putnbr_fd(input / 10, fd);
	output = (input % 10) + '0';
	write (fd, &output, 1);
}
