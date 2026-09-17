/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stack_edge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 19:51:39 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/20 16:12:58 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*get_smallest(t_list *stack)
{
	t_list	*smallest;
	int		cur;

	smallest = stack;
	while (stack)
	{
		cur = *(int *)(stack->content);
		if (cur < *(int *)(smallest->content))
			smallest = stack;
		stack = stack->next;
	}
	return (smallest);
}

t_list	*get_biggest(t_list *stack)
{
	t_list	*biggest;
	int		cur;

	biggest = stack;
	while (stack)
	{
		cur = *(int *)(stack->content);
		if (cur > *(int *)(biggest->content))
			biggest = stack;
		stack = stack->next;
	}
	return (biggest);
}
