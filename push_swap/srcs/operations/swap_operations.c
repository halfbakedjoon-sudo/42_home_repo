/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:46:36 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:42:52 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "push_swap.h"

static void	swap_stack(t_list **stack)
{
	t_list	*first;
	t_list	*second;

	if (ft_lstsize(*stack) < 2)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	swap_both(t_list **stack_a, t_list **stack_b,
	const t_op_params *params, t_operations *counter)
{
	swap_stack(stack_a);
	swap_stack(stack_b);
	if (params->count)
	{
		(counter->ss)++;
		(counter->total)++;
	}
	if (params->print)
		ft_printf(1, "ss\n");
}

void	swap_one(t_list **stack, const t_op_params *params,
	t_operations *counter)
{
	swap_stack(stack);
	if (params->count)
	{
		if (params->stack == A)
			(counter->sa)++;
		else
			(counter->sb)++;
		(counter->total)++;
	}
	if (params->print)
	{
		if (params->stack == A)
			ft_printf(1, "sa\n");
		else
			ft_printf(1, "sb\n");
	}
}
