/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/28 16:15:23 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*next;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	next = *lst;
	while (next->next)
		next = next->next;
	next->next = new;
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(int argc, char **argv)
//{
//	t_list	**out;
//	t_list	*next;
//	t_list	*temp;
//	out = (t_list **)malloc(sizeof(t_list *));
//	out[0] = ft_lstnew((void *)argv[argc - 2]);
//	next = out[0];
//	while (next)
//	{
//		printf("%s\n", (char *)next->content);
//		next = next->next;
//	}
//	printf("\n");
//	ft_lstadd_back(out, ft_lstnew((void *)argv[argc - 1]));
//	next = out[0];
//	while (next)
//	{
//		temp = next;
//		printf("%s\n", (char *)next->content);
//		next = next->next;
//		free(temp);
//	}
//	free(out);
//}
