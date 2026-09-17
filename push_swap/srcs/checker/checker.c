/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:09:51 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 09:25:29 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "push_swap.h"
#include "get_next_line.h"

int	checker(t_list **a, t_list **b, t_parsing *va)
{
	char	*op;

	while (1)
	{
		op = get_next_line(0);
		if (!op)
			break ;
		if (!(checker_swap(a, b, va, op)))
			;
		else if (!(checker_push(a, b, va, op)))
			;
		else if (!(checker_rotate(a, b, va, op)))
			;
		else if (!(checker_rrotate(a, b, va, op)))
			;
		else
			return (checker_op_error_clear(a, b, op), 1);
		free(op);
	}
	return (0);
}
