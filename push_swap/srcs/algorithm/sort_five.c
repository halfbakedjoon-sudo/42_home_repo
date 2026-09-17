/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:12:29 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:44:25 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	sort_five_utils1(t_parsing *va, t_list **b)
{
	if (*(int *)va->lst->content < *(int *)ft_lstlast(va->lst)->content)
	{
		(va->op_params).stack = A;
		if (*(int *)(*b)->content < *(int *)va->lst->content)
		{
			push_one(b, &va->lst, &va->op_params, &va->op_counter);
		}
		else if (*(int *)(*b)->content > *(int *)ft_lstlast(va->lst)->content)
		{
			push_one(b, &va->lst, &va->op_params, &va->op_counter);
			rotate_one(&va->lst, &va->op_params, &va->op_counter);
		}
		else if (*(int *)(*b)->content > *(int *)va->lst->content
				&& *(int *)(*b)->content < *(int *)ft_lstlast(va->lst)->content)
		{
			while (*(int *)(*b)->content > *(int *)va->lst->content)
			{
				rotate_one(&va->lst, &va->op_params, &va->op_counter);
			}
			push_one(b, &va->lst, &va->op_params, &va->op_counter);
		}
	}
}

static int	sort_five_utils3(t_parsing *va, t_list **b)
{
	(va->op_params).stack = A;
	if (*(int *)(*b)->content < *(int *)va->lst->content
		&& *(int *)(*b)->content > *(int *)ft_lstlast(va->lst)->content)
	{
		push_one(b, &va->lst, &va->op_params, &va->op_counter);
		return (0);
	}
	else if ((*(int *)(*b)->content > *(int *)va->lst->content
		&& *(int *)(*b)->content > *(int *)va->lst->content)
		&& *(int *)va->lst->content < *(int *)ft_lstlast(va->lst)->content)
	{
		push_one(b, &va->lst, &va->op_params, &va->op_counter);
		return (0);
	}
	else if ((*(int *)(*b)->content < *(int *)va->lst->content
		&& *(int *)(*b)->content < *(int *)va->lst->content)
		&& *(int *)va->lst->content < *(int *)ft_lstlast(va->lst)->content)
	{
		push_one(b, &va->lst, &va->op_params, &va->op_counter);
		return (0);
	}
	return (1);
}

static void	sort_five_utils2(t_parsing *va, t_list **b)
{
	(va->op_params).stack = A;
	if (*(int *)(*b)->content < *(int *)va->lst->content
		&& *(int *)(*b)->content > *(int *)ft_lstlast(va->lst)->content)
	{
		push_one(b, &va->lst, &va->op_params, &va->op_counter);
	}
	else
	{
		while (1)
		{
			rotate_one(&va->lst, &va->op_params, &va->op_counter);
			if (!(sort_five_utils3(va, b)))
				break ;
		}
		(va->op_params).stack = A;
		rotate_one(&va->lst, &va->op_params, &va->op_counter);
	}
}

static void	sort_five_utils(t_parsing *va, t_list **b)
{
	if (*(int *)(*b)->content > *(int *)(*b)->next->content)
	{
		(va->op_params).stack = B;
		rotate_one(b, &va->op_params, &va->op_counter);
	}
	while (*b)
	{
		if (*(int *)va->lst->content
			< *(int *)ft_lstlast(va->lst)->content)
			sort_five_utils1(va, b);
		else if (*(int *)va->lst->content
			> *(int *)ft_lstlast(va->lst)->content)
			sort_five_utils2(va, b);
	}
	while (compute_disorder(&va->lst) > 0.00)
	{
		(va->op_params).stack = A;
		rotate_one(&va->lst, &va->op_params, &va->op_counter);
	}
}

void	sort_five(t_parsing *va)
{
	t_list	*b;

	b = NULL;
	(va->op_params).stack = B;
	push_one(&va->lst, &b, &va->op_params, &va->op_counter);
	push_one(&va->lst, &b, &va->op_params, &va->op_counter);
	sort_three(va);
	sort_five_utils(va, &b);
}
