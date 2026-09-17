/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:05:31 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:44:21 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"
#include <stdio.h>

static int	count_bits_needed(unsigned int n)
{
	int	bits;
	int	max_rank;

	max_rank = n - 1;
	bits = 0;
	while (max_rank > 0)
	{
		max_rank = max_rank >> 1;
		bits++;
	}
	return (bits);
}

static void	push_to_b(t_parsing *va, t_list **b, int bit)
{
	unsigned int	size;

	size = ft_lstsize(va->lst);
	while (size > 0)
	{
		if (!(compute_disorder(&va->lst) > 0.00)
			&& (compute_disorder(b) == 1))
			break ;
		if (((*(int *)va->lst->content) >> bit) & 1)
		{
			(va->op_params).stack = A;
			rotate_one(&va->lst, &va->op_params, &va->op_counter);
		}
		else
		{
			(va->op_params).stack = B;
			push_one(&va->lst, b, &va->op_params, &va->op_counter);
		}
		size--;
	}
}

static void	push_to_a(t_parsing *va, t_list **b, int bit)
{
	unsigned int	size;

	size = ft_lstsize(*b);
	while (size > 0)
	{
		if (!(compute_disorder(&va->lst) > 0.00)
			&& (compute_disorder(b) == 1))
			break ;
		if (((*(int *)(*b)->content) >> (bit + 1)) & 1)
		{
			(va->op_params).stack = A;
			push_one(b, &va->lst, &va->op_params, &va->op_counter);
		}
		else
		{
			(va->op_params).stack = B;
			rotate_one(b, &va->op_params, &va->op_counter);
		}
		size--;
	}
}

void	radix_binary(t_parsing *va)
{
	t_list			*b;
	int				bit;
	int				total_bits;

	convert_to_ranks(va->lst);
	total_bits = count_bits_needed(ft_lstsize(va->lst));
	b = NULL;
	bit = 0;
	while (bit < total_bits)
	{
		push_to_b(va, &b, bit);
		if (bit + 1 < total_bits)
		{
			push_to_a(va, &b, bit);
		}
		bit++;
	}
	(va->op_params).stack = A;
	while (b)
		push_one(&b, &va->lst, &va->op_params, &va->op_counter);
}
