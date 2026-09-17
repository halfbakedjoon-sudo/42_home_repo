/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 14:12:05 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	digits;

	digits = 1;
	while (n / 10 != 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static int	get_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*out;
	int		size;
	int		stop;

	size = count_digits(n);
	sign = get_sign(n);
	if (n < 0)
		size++;
	out = (char *)malloc((size + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[size] = 0;
	stop = 0;
	if (n < 0)
	{
		out[0] = '-';
		stop++;
	}
	while (--size >= stop)
	{
		out[size] = (n % 10) * sign + '0';
		n /= 10;
	}
	return (out);
}

//#include <stdio.h>
//#include <stdlib.h>
//int	main(int argc, char **argv)
//{
//	char *printme = ft_itoa(atoi(argv[argc - 1]));
//	printf("%s", printme);
//	free(printme);
//}
