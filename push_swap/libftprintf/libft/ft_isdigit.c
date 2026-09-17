/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:36:45 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 17:29:49 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//int main(int argc, char **argv)
//{
//	(void)argc;
//	printf("ft: %d\n", ft_isdigit(argv[1][0]));
//	printf("or: %d\n", isdigit(argv[1][0]));
//}
