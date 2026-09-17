/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:31:51 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 13:47:13 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	out;
	int	sign;
	int	digits;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	out = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	digits = 0;
	while (nptr[digits] >= '0' && nptr[digits] <= '9')
		out = out * 10 + (sign * (nptr[digits++] - '0'));
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	printf("my: %d\n", ft_atoi(argv[argc - 1]));
//	printf("or: %d\n", atoi(argv[argc - 1]));
//}
