/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 13:56:37 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*free_me;

	if (!lst)
		return ;
	while (*lst)
	{
		free_me = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(free_me, del);
	}
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(int argc, char **argv)
//{
//	t_list	**out;
//	int	index = 0;
//
//	out = (t_list **)malloc(sizeof(t_list *));
//	*out = ft_lstnew(ft_strdup(argv[0]));
//	while (++index < argc)
//		ft_lstadd_back(out, ft_lstnew(ft_strdup(argv[index])));
//	ft_lstclear(out, &free);
//	printf("%p", *out);
//	free(out);
//}
