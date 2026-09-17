/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:27:47 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 14:03:33 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	benchmark_op(t_operations *op_counter)
{
	ft_printf(2,
		"\n[bench] sa:  %-5d  sb:  %-5d  ss:  %-5d  pa:  %-5d  pb:  %d",
		op_counter->sa, op_counter->sb, op_counter->ss,
		op_counter->pa, op_counter->pb);
	ft_printf(2,
		"\n[bench] ra:  %-5d  rb:  %-5d  rr:  %-5d  ",
		op_counter->ra, op_counter->rb, op_counter->rr);
	ft_printf(2,
		"rra: %-5d  rrb: %-5d  rrr: %d\n",
		op_counter->rra, op_counter->rrb, op_counter->rrr);
}

void	benchmark(t_operations *op_counter, double disorder, unsigned int mode)
{
	ft_printf(2, "%s:        %d.%d%%\n", "[bench] disorder",
		(int)(disorder * 100), (int)(disorder * 10000) % 100);
	ft_printf(2, "[bench] strategy:        ");
	if (mode == 1)
		ft_printf(2, "Simple / O(n²)");
	else if (mode == 2)
		ft_printf(2, "Medium / O(n√2)");
	else if (mode == 3)
		ft_printf(2, "Complex / O(n log n)");
	else if (mode == 5 || mode == 4)
	{
		if (disorder > 0.5)
			ft_printf(2, "Adaptive / n log n");
		else if (disorder < 0.2)
			ft_printf(2, "Adaptive / O(n²)");
		else
			ft_printf(2, "Adaptive / O(n√2)");
	}
	ft_printf(2, "\n[bench] total_ops:       %d", op_counter->total);
	benchmark_op(op_counter);
}
