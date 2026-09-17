/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 15:00:49 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 11:34:02 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_str(va_list *ap, char *type, size_t *index, int *length)
{
	size_t	n;
	char	*output;

	(void) type;
	n = 0;
	output = va_arg(*ap, char *);
	if (output == NULL)
	{
		write (1, "(null)", 6);
		(*length) += 6;
		*index += 1;
		return ;
	}
	while (output[n])
	{
		write (1, &output[n], 1);
		n++;
		(*length)++;
	}
	*index += 1;
}
