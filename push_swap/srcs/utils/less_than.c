/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_than.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:21:07 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/17 16:33:04 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	is_less_than(const t_list *node1, const t_list *node2)
{
	if (*((int *)(node1->content)) < *((int *)(node2->content)))
		return (1);
	else
		return (0);
}
