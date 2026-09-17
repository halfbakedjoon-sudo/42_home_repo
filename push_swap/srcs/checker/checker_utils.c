/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:45:39 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 14:11:39 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "operations.h"

int	checker_swap(t_list **a, t_list **b, t_parsing *va, char *op)
{
	if (ft_strncmp(op, "sa\n", 3) == 0)
	{
		va->op_params = (t_op_params){A, NOPRINT, COUNT};
		swap_one(a, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "sb\n", 3) == 0)
	{
		va->op_params = (t_op_params){B, NOPRINT, COUNT};
		swap_one(b, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "ss\n", 3) == 0)
	{
		va->op_params = (t_op_params){BOTH, NOPRINT, COUNT};
		swap_both(a, b, &va->op_params, &va->op_counter);
		return (0);
	}
	return (1);
}

int	checker_rotate(t_list **a, t_list **b, t_parsing *va, char *op)
{
	if (ft_strncmp(op, "ra\n", 3) == 0)
	{
		va->op_params = (t_op_params){A, NOPRINT, COUNT};
		rotate_one(a, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "rb\n", 3) == 0)
	{
		va->op_params = (t_op_params){B, NOPRINT, COUNT};
		rotate_one(b, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "rr\n", 3) == 0)
	{
		va->op_params = (t_op_params){BOTH, NOPRINT, COUNT};
		rotate_both(a, b, &va->op_params, &va->op_counter);
		return (0);
	}
	return (1);
}

int	checker_rrotate(t_list **a, t_list **b, t_parsing *va, char *op)
{
	if (ft_strncmp(op, "rra\n", 4) == 0)
	{
		va->op_params = (t_op_params){A, NOPRINT, COUNT};
		rrotate_one(a, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "rrb\n", 4) == 0)
	{
		va->op_params = (t_op_params){B, NOPRINT, COUNT};
		rrotate_one(b, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "rrr\n", 4) == 0)
	{
		va->op_params = (t_op_params){BOTH, NOPRINT, COUNT};
		rrotate_both(a, b, &va->op_params, &va->op_counter);
		return (0);
	}
	return (1);
}

int	checker_push(t_list **a, t_list **b, t_parsing *va, char *op)
{
	if (ft_strncmp(op, "pb\n", 3) == 0)
	{
		va->op_params = (t_op_params){B, NOPRINT, COUNT};
		push_one(a, b, &va->op_params, &va->op_counter);
		return (0);
	}
	else if (ft_strncmp(op, "pa\n", 3) == 0)
	{
		va->op_params = (t_op_params){A, NOPRINT, COUNT};
		push_one(b, a, &va->op_params, &va->op_counter);
		return (0);
	}
	return (1);
}

void	checker_op_error_clear(t_list **a, t_list **b, char *op)
{
	ft_printf(2, "Error\n");
	ft_lstclear(a, free_lst);
	if (b)
		ft_lstclear(b, free_lst);
	free(op);
}
