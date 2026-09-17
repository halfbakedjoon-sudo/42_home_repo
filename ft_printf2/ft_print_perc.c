/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_perc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:40:33 by johiew            #+#    #+#             */
/*   Updated: 2026/08/06 09:35:38 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_perc(va_list *ap, char *type, size_t *index, int *length)
{
	(void) ap;
	(void) type;
	ft_putchar_fd ('%', 1);
	(*length)++;
	*index += 1;
}
