/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_within_range.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:23:22 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/20 16:13:59 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libftprintf.h"

int	has_within_front(t_list **stack, t_bucket_vars *props)
{
	unsigned int	within_front;
	unsigned int	total;

	within_front = 0;
	total = has_within_range(*stack, (props->bucket_ranges)[props->index]);
	if (total)
	{
		if (props->index > 0
			&& (has_within_range(*stack, (props->bucket_ranges)
					[props->index - 1]) != total))
			within_front = 1;
		else if (props->index == 0)
			within_front = 1;
	}
	return (within_front);
}

int	has_within_back(t_list **stack, t_bucket_vars *props)
{
	int				within_back;
	unsigned int	total;

	within_back = 0;
	if (props->index_back >= 0)
	{
		total = has_within_range(*stack, (props->bucket_ranges)[props->index]);
		if (has_within_range(*stack, (props->bucket_ranges)
				[props->index_back]))
		{
			if (props->index_back > 0
				&& has_within_range(*stack, (props->bucket_ranges)
					[props->index_back - 1]) != total)
				within_back = 1;
			else if (props->index_back == 0)
				within_back = 1;
		}
	}
	return (within_back);
}
