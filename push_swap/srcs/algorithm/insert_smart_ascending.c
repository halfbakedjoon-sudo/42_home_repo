/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_smart_ascending.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:56:15 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:09:29 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static int	is_biggest_smallest(int target, t_list *tmp)
{
	if (target <= *(int *)tmp->content && target <= *(int *)tmp->next->content
		&& *(int *)tmp->content >= *(int *)tmp->next->content)
		return (1);
	else if (target >= *(int *)tmp->content
		&& target >= *(int *)tmp->next->content
		&& *(int *)tmp->content >= *(int *)tmp->next->content)
		return (1);
	else
		return (0);
}

int	check_cost_ascending(t_list *b, int target)
{
	int		pos_from_top;
	int		size;
	t_list	*tmp;

	pos_from_top = 0;
	size = ft_lstsize(b);
	tmp = b;
	while (tmp->next && pos_from_top < size)
	{
		if (target >= *(int *)tmp->content
			&& target <= *(int *)tmp->next->content)
		{
			pos_from_top++;
			break ;
		}
		pos_from_top++;
		if (is_biggest_smallest(target, tmp))
			break ;
		tmp = tmp->next;
	}
	if (pos_from_top <= size - pos_from_top)
		return (pos_from_top);
	return (-(size - pos_from_top));
}

static void	checkcost_rotateb(t_list **b, int target, t_parsing *va)
{
	int	n;

	n = check_cost_ascending(*b, target);
	(va->op_params).stack = B;
	if (n > 0)
	{
		while (n > 0)
		{
			rotate_one(b, &va->op_params, &va->op_counter);
			n--;
		}
		n = 0;
	}
	else if (n < 0)
	{
		n *= -1;
		while (n > 0)
		{
			rrotate_one(b, &va->op_params, &va->op_counter);
			n--;
		}
		n = 0;
	}
}

void	insert_smart_ascending(t_list **a, t_list **b, t_parsing *va)
{
	int				target;
	int				top_val;
	int				bot_val;
	unsigned int	size;

	target = *(int *)(*a)->content;
	top_val = *(int *)(*b)->content;
	bot_val = *(int *)ft_lstlast(*b)->content;
	size = ft_lstsize(*b);
	if (top_val < bot_val)
	{
		if (target > top_val && target > bot_val)
			;
		else if (target > top_val && target < bot_val)
			checkcost_rotateb(b, target, va);
	}
	else
	{
		if (!(target < *(int *)(*b)->content
			&& target > *(int *)ft_lstlast(*b)->content))
			checkcost_rotateb(b, target, va);
	}
	(va->op_params).stack = B;
	push_one(a, b, &va->op_params, &va->op_counter);
}
