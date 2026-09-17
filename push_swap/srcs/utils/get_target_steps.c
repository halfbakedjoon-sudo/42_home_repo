/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target_steps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:40:11 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/20 15:40:35 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	get_steps_to_target(t_list *stack, t_list *target)
{
	unsigned int	steps;

	steps = 0;
	while (stack != target)
	{
		stack = stack->next;
		steps++;
	}
	return (steps);
}
