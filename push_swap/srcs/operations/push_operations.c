/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:46:36 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 13:41:44 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "push_swap.h"

static void	push_stack(t_list **stack_src, t_list **stack_dest)
{
	t_list	*pushed;
	int		empty;

	empty = 0;
	if (ft_lstsize(*stack_src) < 1)
		return ;
	if (ft_lstsize(*stack_src) == 1)
		empty = 1;
	pushed = *stack_src;
	*stack_src = (*stack_src)->next;
	pushed->next = NULL;
	ft_lstadd_front(stack_dest, pushed);
	if (empty)
		*stack_src = NULL;
}

void	push_one(t_list **stack_src, t_list **stack_dest,
	const t_op_params *params, t_operations *counter)
{
	push_stack(stack_src, stack_dest);
	if (params->count)
	{
		if (params->stack == A)
			(counter->pa)++;
		else
			(counter->pb)++;
		(counter->total)++;
	}
	if (params->print)
	{
		if (params->stack == A)
			ft_printf(1, "pa\n");
		else
			ft_printf(1, "pb\n");
	}
}
