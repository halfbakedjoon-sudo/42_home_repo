/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 08:55:23 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:44:30 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

int	main(int argc, char **argv)
{
	t_parsing	va;
	t_list		*b;

	if (ft_checkargc(argc))
		return (0);
	if (all_check(&va, argv))
		return (0);
	va.total = ft_lstsize(va.lst);
	b = NULL;
	if (checker(&va.lst, &b, &va))
		return (0);
	if (compute_disorder(&va.lst) > 0.00 || b)
	{
		ft_printf(1, "KO\n");
		ft_lstclear(&va.lst, free_lst);
		if (b)
			ft_lstclear(&b, free_lst);
		return (0);
	}
	else
		ft_printf(1, "OK\n");
	ft_lstclear(&va.lst, free_lst);
	return (0);
}
