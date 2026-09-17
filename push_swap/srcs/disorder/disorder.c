/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:06:14 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/26 15:16:43 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	compute_disorder(t_list **stack)
{
	t_list			*current;
	t_list			*compare;
	unsigned int	total_pairs;
	unsigned int	mistakes;

	if (!*stack || !(*stack)->next)
		return (0.00);
	total_pairs = 0;
	mistakes = 0;
	current = *stack;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			total_pairs++;
			if (*(int *)current->content > *(int *)compare->content)
				mistakes++;
			compare = compare->next;
		}
		current = current->next;
	}
	return ((double)mistakes / (double)total_pairs);
}
