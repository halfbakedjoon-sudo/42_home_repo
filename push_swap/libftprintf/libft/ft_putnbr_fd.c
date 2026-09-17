/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 14:44:15 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10 * (1 + (-2 * (n < 0))), fd);
	ft_putchar_fd('0' + ((n % 10) * (1 + (-2 * (n < 0)))), fd);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(int argc, char **argv)
//{
//	ft_putnbr_fd(atoi(argv[argc - 1]), 1);
//}
