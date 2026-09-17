/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 15:44:08 by thdexmun          #+#    #+#             */
/*   Updated: 2026/08/02 15:07:13 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;

	temp = (char *)s;
	while (temp && n--)
		*temp++ = 0;
}

//#include <stdio.h>
//int main(int argc, char **argv)
//{
//	int	size = 0;
//	int index = 0;
//	while (argv[argc - 1][size])
//		size++;
//	ft_bzero(argv[argc - 1], 4);
//	while (index < size)
//		write (1, &(argv[argc - 1][index++]), 1);
//}
