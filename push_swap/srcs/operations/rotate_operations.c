/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:46:36 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:42:04 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "push_swap.h"

static void	rotate_stack(t_list **stack)
{
	t_list	*original_first;
	t_list	*new_first;

	if (!*stack || !(*stack)->next)
		return ;
	original_first = *stack;
	new_first = (*stack)->next;
	original_first->next = NULL;
	*stack = new_first;
	ft_lstadd_back(stack, original_first);
}

void	rotate_both(t_list **stack_a, t_list **stack_b,
	const t_op_params *params, t_operations *counter)
{
	rotate_stack(stack_a);
	rotate_stack(stack_b);
	if (params->count)
	{
		(counter->rb)++;
		(counter->total)++;
	}
	if (params->print)
		ft_printf(1, "rr\n");
}

void	rotate_one(t_list **stack, const t_op_params *params,
	t_operations *counter)
{
	rotate_stack(stack);
	if (params->count)
	{
		if (params->stack == A)
			(counter->ra)++;
		else
			(counter->rb)++;
		(counter->total)++;
	}
	if (params->print)
	{
		if (params->stack == A)
			ft_printf(1, "ra\n");
		else
			ft_printf(1, "rb\n");
	}
}
