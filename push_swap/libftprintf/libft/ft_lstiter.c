/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 16:05:33 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

//#include <stdio.h>
//#include <stdlib.h>
//
//void	test(void *a)
//{
//	printf("%s\n", (char *)a);
//}
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
//	ft_lstiter(*out, &test);
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
