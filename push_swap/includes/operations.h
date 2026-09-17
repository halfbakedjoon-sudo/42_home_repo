/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:47:21 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/24 16:58:50 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

void	push_one(t_list **stack_src, t_list **stack_dest,
			const t_op_params *params, t_operations *counter);
void	swap_both(t_list **stack_a, t_list **stack_b,
			const t_op_params *params, t_operations *counter);
void	swap_one(t_list **stack, const t_op_params *params,
			t_operations *counter);
void	rotate_both(t_list **stack_a, t_list **stack_b,
			const t_op_params *params, t_operations *counter);
void	rotate_one(t_list **stack, const t_op_params *params,
			t_operations *counter);
void	rrotate_both(t_list **stack_a, t_list **stack_b,
			const t_op_params *params, t_operations *counter);
void	rrotate_one(t_list **stack, const t_op_params *params,
			t_operations *counter);

#endif
