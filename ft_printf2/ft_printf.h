/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johiew <johiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 09:48:16 by johiew            #+#    #+#             */
/*   Updated: 2026/08/05 18:42:43 by johiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

int		ft_printf(const char *s, ...);
void	ft_print_int(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_char(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_str(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_ptr(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_u(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_lowerx(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_upperx(va_list *ap, char *type, size_t *index, int *length);
void	ft_print_perc(va_list *ap, char *type, size_t *index, int *length);
void	ft_convert(va_list *ap, char *type, size_t *index, int *length);

#endif
