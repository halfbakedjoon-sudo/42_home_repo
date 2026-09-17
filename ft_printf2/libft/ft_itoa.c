/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:52:46 by johiew            #+#    #+#             */
/*   Updated: 2026/07/31 10:04:32 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	result(long input, int index, char *arry)
{
	arry[index] = '\0';
	index--;
	while (input)
	{
		arry[index] = (input % 10) + '0';
		input /= 10;
		index--;
	}
}

char	*ft_itoa(int n)
{
	char	*arry;
	long	input;
	int		len;

	input = n;
	len = count_digit(input);
	arry = malloc(len + 1);
	if (!arry)
		return (NULL);
	if (input == 0)
	{
		arry[0] = '0';
		arry[1] = '\0';
		return (arry);
	}
	if (input < 0)
	{
		arry[0] = '-';
		input *= -1;
	}
	result(input, len, arry);
	return (arry);
}

/*int	main(void)
{
	char	*result = ft_itoa(2147483647);
	int	n = 0;
	while (result[n])
	{
		write (1, &result[n], 1);
		n++;
	}
	free (result);
	return (0);
}*/
