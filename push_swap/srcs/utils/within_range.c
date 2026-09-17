/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   within_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:11:17 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/19 21:15:18 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	within_range(t_list *stack, int range)
{
	if (*(int *)(stack->content) <= range)
		return (1);
	return (0);
}

unsigned int	has_within_range(t_list *stack, int range)
{
	unsigned int	count;

	count = 0;
	while (stack)
	{
		if (within_range(stack, range))
			count++;
		stack = stack->next;
	}
	return (count);
}
