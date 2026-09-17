/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:36:45 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 13:48:52 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//int main(int argc, char **argv)
//{
//	(void)argc;
//	printf("ft: %d\n", ft_isalnum(argv[1][0]));
//	printf("or: %d\n", isalnum(argv[1][0]));
//}
