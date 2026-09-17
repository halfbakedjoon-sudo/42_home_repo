/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:59:07 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/19 21:26:29 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	sqrt_floor(unsigned int num)
{
	unsigned int	sqrt;

	if (num == 0)
		return (0);
	sqrt = 1;
	while (num / sqrt > sqrt)
		sqrt++;
	return (sqrt);
}
