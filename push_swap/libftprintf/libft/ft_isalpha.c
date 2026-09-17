/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:36:45 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 17:29:38 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 'A' || c > 'z')
		return (0);
	if (c > 'Z' && c < 'a')
		return (0);
	return (1);
}

//#include <stdio.h>
//#include <ctype.h>
//int main(int argc, char **argv)
//{
//	(void)argc;
//	printf("ft: %d\n", ft_isalpha(argv[1][0]));
//	printf("or: %d\n", isalpha(argv[1][0]));
//}
