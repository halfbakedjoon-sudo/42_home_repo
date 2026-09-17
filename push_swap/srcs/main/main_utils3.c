/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 19:03:32 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 14:11:24 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_checkargc(int argc)
{
	if (argc < 2)
	{
		return (1);
	}
	return (0);
}

char	*ft_joinargv(char **argv)
{
	long long		n;
	char			*str;
	char			*tmp;
	char			*piece;

	n = 1;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (argv[n])
	{
		piece = ft_strjoin(argv[n], " ");
		if (!piece)
			return (free(str), NULL);
		tmp = ft_strjoin(str, piece);
		free(str);
		free(piece);
		if (!tmp)
			return (NULL);
		str = tmp;
		n++;
	}
	return (str);
}

int	check_dup(t_parsing *va)
{
	while (va->tmp)
	{
		va->value = *(int *)va->tmp->content;
		while (va->tmp2)
		{
			if (va->value == *(long long *)va->tmp2->content)
			{
				ft_printf(2, "Error\n");
				ft_lstclear(&va->lst, free_lst);
				return (1);
			}
			va->tmp2 = va->tmp2->next;
		}
		va->tmp = va->tmp->next;
		if (va->tmp)
			va->tmp2 = va->tmp->next;
	}
	return (0);
}

int	all_check(t_parsing *va, char **argv)
{
	char		**list_str;
	char		*str;
	char		*tmp;

	tmp = NULL;
	ft_bzero(va, sizeof(t_parsing));
	str = ft_joinargv(argv);
	tmp = check_mode(va, str);
	list_str = ft_split(tmp, ' ');
	free(str);
	if (!list_str)
		return (1);
	if (check_valid_conlst(va, list_str))
		return (1);
	free_split(list_str);
	va->tmp = va->lst;
	if (va->lst)
		va->tmp2 = va->lst->next;
	if (check_dup(va))
		return (1);
	return (0);
}
