/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_insertion_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 13:14:25 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/27 14:35:19 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	set_steps(t_setsteps_vars *props, unsigned int ret[2])
{
	unsigned int	temp;
	unsigned int	temp2;

	temp = props->stepa;
	if (props->stepa > props->stack_size / 2)
		temp = props->stack_size - props->stepa;
	if (props->stepb > props->stackb_size / 2)
		temp += props->stackb_size - props->stepb;
	else
		temp += props->stepb;
	if (props->set)
	{
		temp2 = ret[0];
		if (ret[0] > props->stack_size / 2)
			temp2 = props->stack_size - ret[0];
		if (ret[1] > props->stackb_size / 2)
			temp2 += props->stackb_size - ret[1];
		else
			temp2 += ret[1];
	}
	if (!props->set || temp < temp2)
	{
		ret[0] = props->stepa;
		ret[1] = props->stepb;
	}
}

static void	get_target(t_list **target, t_list *biggest,
	t_list *iter, t_list **stack)
{
	while (*target != biggest)
	{
		if (is_less_than(iter, *target))
			break ;
		*target = (*target)->next;
		if (*target == NULL)
			*target = *stack;
	}
	if (!is_less_than(iter, *target))
		*target = get_smallest(*stack);
}

static void	get_rotate_target(t_list **stack, t_list **stack_b,
	unsigned int ret[2], t_bucket_vars *props)
{
	t_setsteps_vars	setter;
	t_list			*iter;
	t_list			*target;
	t_list			*biggest;

	iter = props->stack_b_top;
	setter.stack_size = ft_lstsize(*stack);
	setter.stackb_size = ft_lstsize(*stack_b);
	setter.set = 0;
	while (is_within_front(&iter, props))
	{
		target = get_smallest(*stack);
		biggest = get_biggest(*stack);
		get_target(&target, biggest, iter, stack);
		setter.stepa = get_steps_to_target(*stack, target);
		setter.stepb = get_steps_to_target(*stack_b, iter);
		set_steps(&setter, ret);
		setter.set = 1;
		iter = iter->next;
		if (!iter)
			iter = *stack_b;
		if (iter == props->stack_b_top)
			break ;
	}
}

static void	rotate_to_target(t_list **stack, t_op_stack code,
	t_parsing *parsing, unsigned int count)
{
	unsigned int	size;

	size = ft_lstsize(*stack);
	(parsing->op_params).stack = code;
	if (size / 2 > count)
		while (count--)
			rotate_one(stack, &parsing->op_params, &parsing->op_counter);
	else
		while (count++ < size)
			rrotate_one(stack, &parsing->op_params, &parsing->op_counter);
}

void	bucket_insertion_sort(t_list **stack, t_list **stack_b,
	t_bucket_vars *props, t_parsing *parsing)
{
	unsigned int	steps[2];

	while (1)
	{
		if (*stack_b == props->stack_b_top)
		{
			props->stack_b_top = (props->stack_b_top)->next;
			if (!props->stack_b_top)
				props->stack_b_top = *stack_b;
		}
		(parsing->op_params).stack = A;
		push_one(stack_b, stack, &parsing->op_params, &parsing->op_counter);
		if (!*stack_b)
			break ;
		if (!(*stack)->next)
			continue ;
		while (!is_within_front(&(props->stack_b_top), props))
			(props->index)--;
		ft_bzero(steps, 2 * sizeof(unsigned int));
		get_rotate_target(stack, stack_b, (unsigned int *)steps, props);
		rotate_to_target(stack, A, parsing, steps[0]);
		rotate_to_target(stack_b, B, parsing, steps[1]);
	}
	rotate_to_target(stack, A, parsing,
		get_steps_to_target(*stack, get_smallest(*stack)));
}
