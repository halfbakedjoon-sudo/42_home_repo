/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:11:15 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:10:30 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	sort_three_utils(int top, int mid, int btm, t_parsing *va)
{
	(va->op_params).stack = A;
	if (top < mid && top < btm && mid > btm)
	{
		rrotate_one(&va->lst, &va->op_params, &va->op_counter);
		swap_one(&va->lst, &va->op_params, &va->op_counter);
	}
	else if (top > mid && top < btm && mid < btm)
	{
		swap_one(&va->lst, &va->op_params, &va->op_counter);
	}
	else if (top < mid && top > btm && mid > btm)
		rrotate_one(&va->lst, &va->op_params, &va->op_counter);
}

void	sort_three(t_parsing *va)
{
	int	top;
	int	mid;
	int	btm;

	top = *(int *)va->lst->content;
	mid = *(int *)va->lst->next->content;
	btm = *(int *)va->lst->next->next->content;
	(va->op_params).stack = A;
	if (top > mid && top > btm && mid > btm)
	{
		rotate_one(&va->lst, &va->op_params, &va->op_counter);
		swap_one(&va->lst, &va->op_params, &va->op_counter);
	}
	else if (top > mid && top > btm & mid < btm)
	{
		rotate_one(&va->lst, &va->op_params, &va->op_counter);
	}
	else
		sort_three_utils(top, mid, btm, va);
}

void	simple(t_parsing *va)
{
	convert_to_ranks(va->lst);
	if (va->total > 3)
	{
		sort_five(va);
	}
	else
	{
		sort_three(va);
	}
}
