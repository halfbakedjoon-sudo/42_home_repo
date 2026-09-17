/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:11:15 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:08:33 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	first_operation(t_parsing *va, t_list **b)
{
	(va->op_params).stack = B;
	push_one(&va->lst, b, &va->op_params, &va->op_counter);
	push_one(&va->lst, b, &va->op_params, &va->op_counter);
	if (*(int *)(*b)->content < *(int *)(*b)->next->content)
		rotate_one(b, &va->op_params, &va->op_counter);
}

static void	rewind_before_push(t_parsing *va, t_list **b, unsigned int max)
{
	int				n;

	(va->op_params).stack = B;
	n = check_cost_descending(*b, 0);
	if (*(unsigned int *)(*b)->content != max)
	{
		if (n > 0)
		{
			while (*(unsigned int *)(*b)->content != max)
				rotate_one(b, &va->op_params, &va->op_counter);
		}
		else if (n < 0)
		{
			n *= -1;
			while (*(unsigned int *)(*b)->content != max)
				rrotate_one(b, &va->op_params, &va->op_counter);
		}
	}
}

void	insertion_alt(t_parsing *va)
{
	t_list			*b;
	unsigned int	max;
	unsigned int	size;

	size = ft_lstsize(va->lst);
	max = size - 1;
	b = NULL;
	convert_to_ranks(va->lst);
	first_operation(va, &b);
	while (va->lst)
		insert_smart_descending(&va->lst, &b, va);
	rewind_before_push(va, &b, max);
	va->tmp = b;
	(va->op_params).stack = A;
	while (b)
	{
		push_one(&b, &va->lst, &va->op_params, &va->op_counter);
	}
}
