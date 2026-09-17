/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 16:48:36 by johiew            #+#    #+#             */
/*   Updated: 2026/08/15 15:31:38 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_lst(void *lst)
{
	free(lst);
}

int	is_valid_num(char *input)
{
	int	n;

	n = 0;
	while (input[n])
	{
		if (input[n] == '-' || input[n] == '+')
			n++;
		if (!ft_isdigit(input[n]))
			return (1);
		n++;
	}
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

long long	ft_atoll(const char *nptr)
{
	long long	out;
	int			sign;
	int			digits;

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
