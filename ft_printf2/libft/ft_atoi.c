/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 09:04:41 by johiew            #+#    #+#             */
/*   Updated: 2026/07/29 09:47:03 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;
	int	result;

	n = 0;
	sign = 1;
	result = 0;
	while (nptr[n] == ' ' || (nptr[n] >= '\t' && nptr[n] <= '\r'))
		n++;
	if (nptr[n] == '-')
	{
		sign = -1;
		n++;
	}
	else if (nptr[n] == '+')
	{
		n++;
	}
	while (nptr[n] >= '0' && nptr[n] <= '9')
	{
		result = (result * 10) + (nptr[n] - '0');
		n++;
	}
	return (result * sign);
}
