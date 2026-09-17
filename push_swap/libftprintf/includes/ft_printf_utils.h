/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:42:25 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/03 16:17:36 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include "libft.h"
# include <stdarg.h>

char	*ft_handle_conv(const char *str, int *size, va_list args, int handled);
void	ft_convert(char print, va_list args, int handled, int *size);
void	print_c(int c, int *size);
void	print_s(const char *str, int *size);
void	print_p(void *p, int *size);
void	print_hex(unsigned long long i, int *size, int mode);
void	print_x(unsigned int num, int *size, char conv);
void	print_d(int num, int *size);
void	print_u(unsigned int num, int *size);
void	print_reg(char print, int *size, int handled);

#endif
