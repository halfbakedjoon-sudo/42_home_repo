/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:30:34 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:50:52 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static void	algo_decision(t_parsing *va, double disorder)
{
	va->op_params = (t_op_params){NOSTACK, PRINT, COUNT};
	if (va->total <= 5)
		simple(va);
	else
	{
		if (va->mode == SIMPLE)
			insertion_alt(va);
		else if (va->mode == MEDIUM)
			bucket_sort(&va->lst, va);
		else if (va->mode == COMPLEX)
			radix_binary(va);
		else if (va->mode == NONE || va->mode == ADAPTIVE)
		{
			if (disorder > 0.5)
				radix_binary(va);
			else if (disorder < 0.2)
				insertion_alt(va);
			else
				bucket_sort(&va->lst, va);
		}
	}
}

int	main(int argc, char **argv)
{
	t_parsing		va;
	double			disorder;

	if (ft_checkargc(argc))
		return (0);
	if (all_check(&va, argv))
		return (0);
	disorder = compute_disorder(&va.lst);
	if (!(disorder > 0.00))
		return (0);
	va.total = ft_lstsize(va.lst);
	algo_decision(&va, disorder);
	if (va.bench == 1)
	{
		benchmark(&va.op_counter, disorder, va.mode);
	}
	ft_lstclear(&va.lst, free_lst);
	return (0);
}
