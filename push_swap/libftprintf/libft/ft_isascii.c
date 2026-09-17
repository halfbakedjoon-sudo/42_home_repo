/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:36:45 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/25 15:00:17 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//int main(int argc, char **argv)
//{
//	(void)argc;
//	(void)argv;
//	printf("ft: %d\n", ft_isascii(127));
//	printf("or: %d\n", isascii(127));
//}
