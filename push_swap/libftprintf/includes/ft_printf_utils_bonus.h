/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:42:25 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/04 20:18:38 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_BONUS_H
# define FT_PRINTF_UTILS_BONUS_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_print	t_print;
typedef struct s_handle	t_handle;

char	*ft_handle_conv(const char *str, int *size,
			va_list args, t_handle *handled);
void	ft_convert(t_print print, va_list args, int *size, t_handle *handled);
void	print_c(t_print print, int c, int *size, int fd);
void	print_s(t_print print, const char *str, int *size, int fd);
void	print_p(t_print print, void *p, int *size, int fd);
void	print_hex(unsigned long long i, int mode, int fd);
void	print_x(t_print print, unsigned int num, int *size, int fd);
void	print_d(t_print print, int num, int *size, int fd);
void	print_u(t_print print, unsigned int num, int *size, int fd);
void	print_reg(t_print print, int *size, int handled, int fd);
void	print_spaces(int *tsize, int width, int fd);
int		count_base(unsigned long long num, unsigned long long base);
int		get_numconvsize(int *zeros, t_print print, unsigned int num, int base);
void	print_spaceplus(t_print print, int num, int fd);

typedef struct s_print
{
	char	handle_hash;
	char	handle_plus;
	char	handle_minus;
	char	handle_zero;
	char	handle_space;
	char	handle_prec;
	int		width;
	int		precision;
	char	conversion;
}	t_print;

typedef struct s_handle
{
	int	handled;
	int	fd;
}	t_handle;

#endif
