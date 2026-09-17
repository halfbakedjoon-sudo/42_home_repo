/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:54:02 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/08 18:23:33 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

char	*ft_handle_conv(const char *str, int *size, va_list args, int handled)
{
	char		print;

	str++;
	print = *str;
	ft_convert(print, args, handled, size);
	if (*str)
		return ((char *)++str);
	return ((char *)str);
}
