/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:36:45 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 17:30:23 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//int main(int argc, char **argv)
//{
//	(void)argc;
//	(void)argv;
//	printf("ft: %d\n", ft_isprint(argv[1][0]));
//	printf("or: %d\n", isprint(argv[1][0]));
//}
