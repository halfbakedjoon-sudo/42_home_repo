/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 15:36:32 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	size;

	size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(int argc, char **argv)
//{
//	t_list	**out;
//	int	index = 0;
//	t_list *temp;
//	t_list *temp2;
//
//	out = (t_list **)malloc(sizeof(t_list *));
//	*out = ft_lstnew((void *)argv[0]);
//	while (++index < argc)
//		ft_lstadd_back(out, ft_lstnew(argv[index]));
//	printf("%u\n", ft_lstsize(*out));
//	temp = *out;
//	while (temp)
//	{
//		printf("%s, ", (char *)temp->content);
//		temp2 = temp;
//		temp = temp->next;
//		free(temp2);
//	}
//	free(out);
//}
