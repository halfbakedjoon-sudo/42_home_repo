/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 13:56:24 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
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
//	*out = ft_lstnew(ft_strdup(argv[0]));
//	while (++index < argc)
//		ft_lstadd_back(out, ft_lstnew(ft_strdup(argv[index])));
//	temp = (*out)->next;
//	ft_lstdelone(*out, &free);
//	while (temp)
//	{
//		printf("%s, ", (char *)temp->content);
//		temp2 = temp;
//		temp = temp->next;
//		free(temp2->content);
//		free(temp2);
//	}
//	free(out);
//}
