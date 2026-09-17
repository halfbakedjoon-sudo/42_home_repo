/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:47:21 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/20 15:40:49 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libftprintf.h"
# include "push_swap.h"

int				is_less_than(const t_list *node1, const t_list *node2);
unsigned int	sqrt_floor(unsigned int num);
t_list			*get_smallest(t_list *stack);
t_list			*get_biggest(t_list *stack);
unsigned int	within_range(t_list *stack, int range);
unsigned int	has_within_range(t_list *stack, int range);
int				is_within_front(t_list **stack, t_bucket_vars *props);
int				is_within_back(t_list **stack, t_bucket_vars *props);
int				has_within_front(t_list **stack, t_bucket_vars *props);
int				has_within_back(t_list **stack, t_bucket_vars *props);
unsigned int	get_steps_to_target(t_list *stack, t_list *target);

#endif
