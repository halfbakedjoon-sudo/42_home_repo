/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:52:51 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 13:40:35 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_sort(t_parsing *va)
{
	va->tmp = va->lst;
	while (va->tmp)
	{
		ft_printf(1, "|%11i|\n", *(int *)va->tmp->content);
		va->tmp = va->tmp->next;
	}
}

static void	setup_mode(t_op_mode mode, t_op_mode *set,
	char *set_tmp, char **tmp)
{
	*set = mode;
	*tmp = set_tmp;
}

char	*check_mode(t_parsing *va, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	if (str)
	{
		if (ft_strnstr(str, "--bench", 7))
		{
			va->bench = 1;
			tmp = str + 8;
		}
		if (ft_strnstr(tmp, "--adaptive", 10))
			setup_mode(ADAPTIVE, &va->mode, tmp + 10, &tmp);
		else if (ft_strnstr(tmp, "--complex", 9))
			setup_mode(COMPLEX, &va->mode, tmp + 9, &tmp);
		else if (ft_strnstr(tmp, "--medium", 8))
			setup_mode(MEDIUM, &va->mode, tmp + 8, &tmp);
		else if (ft_strnstr(tmp, "--simple", 8))
			setup_mode(SIMPLE, &va->mode, tmp + 8, &tmp);
		else
			setup_mode(ADAPTIVE, &va->mode, tmp, &tmp);
	}
	return (tmp);
}
