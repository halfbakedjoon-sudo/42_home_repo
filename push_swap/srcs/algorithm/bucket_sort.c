/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:55:31 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 14:29:51 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	check_and_push(t_list **stack, t_list **stack_b,
	t_parsing *parse, t_bucket_vars *props)
{
	(parse->op_params).stack = A;
	if (*stack && !is_within_back(stack, props)
		&& !is_within_front(stack, props))
		rotate_one(stack, &parse->op_params, &parse->op_counter);
	(parse->op_params).stack = B;
	while (*stack && (is_within_back(stack, props)
			|| is_within_front(stack, props)))
	{
		push_one(stack, stack_b, &parse->op_params, &parse->op_counter);
		while (*stack && is_within_front(stack, props)
			&& is_within_back(stack_b, props)
			&& (props->index - props->index_back > 1
				|| has_within_front(stack_b, props)))
			rotate_one(stack_b, &parse->op_params, &parse->op_counter);
	}
	(parse->op_params).stack = BOTH;
	while (*stack && !is_within_back(stack, props)
		&& !is_within_front(stack, props)
		&& (*stack_b && is_within_back(stack_b, props)))
		rotate_both(stack, stack_b, &parse->op_params, &parse->op_counter);
	(parse->op_params).stack = B;
	while (*stack_b && is_within_back(stack_b, props)
		&& (has_within_front(stack_b, props)
			|| props->index - props->index_back > 1))
		rotate_one(stack_b, &parse->op_params, &parse->op_counter);
}

static void	sort_to_stackb(t_list **stack, t_list **stack_b,
	t_parsing *parsing, t_bucket_vars *props)
{
	props->index = 0;
	props->bucket_ranges = (int *)malloc(props->bucket_size * sizeof(int));
	if (!(props->bucket_ranges))
		return ;
	while (props->index < props->bucket_size)
	{
		(props->bucket_ranges)[(props->index)++] = props->range;
		props->range += props->bucket_volume;
	}
	(props->bucket_ranges)[props->bucket_size - 1]
		= *(int *)(get_biggest(*stack)->content);
	props->index /= 2;
	props->index_back = props->index - 1;
	while (props->index < props->bucket_size)
	{
		while (has_within_front(stack, props) || has_within_back(stack, props))
			check_and_push(stack, stack_b, parsing, props);
		(props->index)++;
		(props->index_back)--;
	}
	props->stack_b_top = (*stack_b)->next;
	props->index = props->bucket_size - 1;
	bucket_insertion_sort(stack, stack_b, props, parsing);
	free(props->bucket_ranges);
}

void	bucket_sort(t_list **stack, t_parsing *parsing)
{
	t_bucket_vars	props;
	t_list			**stack_b;
	long long		diff;

	props.bucket_size = sqrt_floor(parsing->total);
	if (props.bucket_size == 0)
		return ;
	stack_b = malloc(sizeof(t_list *));
	if (!stack_b)
		return ;
	*stack_b = NULL;
	props.smallest = *(int *)(get_smallest(*stack)->content);
	diff = ((long long)*(int *)(get_biggest(*stack)->content)
			- (long long)props.smallest + 1);
	props.bucket_volume = diff / props.bucket_size;
	props.range = props.bucket_volume + props.smallest;
	sort_to_stackb(stack, stack_b, parsing, &props);
	free(stack_b);
}
