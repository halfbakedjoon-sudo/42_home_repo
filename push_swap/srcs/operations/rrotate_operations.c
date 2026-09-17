/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:46:36 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:42:31 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "push_swap.h"

static void	rrotate_stack(t_list **stack)
{
	t_list	*original_last;
	t_list	*new_last;

	if (!*stack || !(*stack)->next)
		return ;
	original_last = ft_lstlast(*stack);
	new_last = *stack;
	while (new_last->next != original_last)
		new_last = new_last->next;
	new_last->next = NULL;
	ft_lstadd_front(stack, original_last);
}

void	rrotate_both(t_list **stack_a, t_list **stack_b,
	const t_op_params *params, t_operations *counter)
{
	rrotate_stack(stack_a);
	rrotate_stack(stack_b);
	if (params->count)
	{
		(counter->rrr)++;
		(counter->total)++;
	}
	if (params->print)
		ft_printf(1, "rrr\n");
}

void	rrotate_one(t_list **stack, const t_op_params *params,
	t_operations *counter)
{
	rrotate_stack(stack);
	if (params->count)
	{
		if (params->stack == A)
			(counter->rra)++;
		else
			(counter->rrb)++;
		(counter->total)++;
	}
	if (params->print)
	{
		if (params->stack == A)
			ft_printf(1, "rra\n");
		else
			ft_printf(1, "rrb\n");
	}
}
