/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 14:01:29 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 14:11:13 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_range(t_parsing *va, char **list_str, long long *node_value)
{
	if (*node_value > INT_MAX || *node_value < INT_MIN)
	{
		free(node_value);
		free_split(list_str);
		ft_lstclear(&va->lst, free_lst);
		return (1);
	}
	return (0);
}

static int	check_validnlen(t_parsing *va, char **list_str)
{
	if (is_valid_num(list_str[va->index])
		|| ft_strlen(list_str[va->index]) > 11)
	{
		free_split(list_str);
		ft_lstclear(&va->lst, free_lst);
		return (1);
	}
	return (0);
}

static int	check_node(t_parsing *va, char **list_str, long long *node_value)
{
	if (!node_value)
	{
		free_split(list_str);
		ft_lstclear(&va->lst, free_lst);
		return (1);
	}
	return (0);
}

int	check_valid_conlst(t_parsing *va, char **list_str)
{
	long long	*node_value;

	while (list_str[va->index])
	{
		if (check_validnlen(va, list_str))
			return ((ft_printf(2, "Error\n")), 1);
		node_value = malloc(2 * sizeof(long long));
		if (check_node(va, list_str, node_value))
			return (1);
		node_value[0] = ft_atoll(list_str[va->index]);
		node_value[1] = node_value[0] + 2147483648;
		if (check_range(va, list_str, node_value))
			return ((ft_printf(2, "Error\n")), 1);
		va->new_node = ft_lstnew(node_value);
		if (!va->new_node)
		{
			free(node_value);
			free_split(list_str);
			ft_lstclear(&va->lst, free_lst);
			return (1);
		}
		ft_lstadd_back(&va->lst, va->new_node);
		va->index++;
	}
	return (0);
}
