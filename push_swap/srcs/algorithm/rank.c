/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 15:49:29 by johiew            #+#    #+#             */
/*   Updated: 2026/08/26 15:44:28 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "operations.h"

static int	get_rank(t_list *lst, long long target)
{
	int		rank;
	t_list	*tmp;

	rank = 0;
	tmp = lst;
	while (tmp)
	{
		if (*(long long *)tmp->content < target)
			rank++;
		tmp = tmp->next;
	}
	return (rank);
}

static void	put_ranks(t_list *tmp, int *ranks)
{
	int	i;
	int	*new_value;

	i = 0;
	while (tmp)
	{
		new_value = malloc(sizeof(int));
		if (!new_value)
			return (free(ranks));
		*new_value = ranks[i];
		free(tmp->content);
		tmp->content = new_value;
		tmp = tmp->next;
		i++;
	}
}

void	convert_to_ranks(t_list *lst)
{
	t_list	*tmp;
	int		*ranks;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	ranks = malloc(sizeof(int) * size);
	if (!ranks)
		return ;
	tmp = lst;
	i = 0;
	while (tmp)
	{
		ranks[i] = get_rank(lst, *(int *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	tmp = lst;
	put_ranks(tmp, ranks);
	free(ranks);
}
