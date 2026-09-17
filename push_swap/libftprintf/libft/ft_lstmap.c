/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/30 13:58:52 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*created;

	first = NULL;
	while (lst)
	{
		created = ft_lstnew(f(lst->content));
		if (!created)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		if (!first)
			first = created;
		else
			ft_lstadd_back(&first, created);
		lst = lst->next;
	}
	return (first);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//void	*test(void *a)
//{
//	return (void *)ft_strdup((char *)a);
//}
//
//int	main(int argc, char **argv)
//{
//	t_list	**out;
//	t_list	**new;
//	int	index = 0;
//	t_list *temp;
//	t_list *temp2;
//
//	out = (t_list **)malloc(sizeof(t_list *));
//	new = (t_list **)malloc(sizeof(t_list *));
//	*out = ft_lstnew(ft_strdup(argv[0]));
//	while (++index < argc)
//		ft_lstadd_back(out, ft_lstnew(ft_strdup(argv[index])));
//	*new = ft_lstmap(*out, &test, &free);
//	temp = *new;
//	while (*out)
//	{
//		temp2 = *out;
//		*out = (*out)->next;
//		free(temp2->content);
//		free(temp2);
//	}
//	while (temp)
//	{
//		printf("%s, ", (char *)temp->content);
//		temp2 = temp;
//		temp = temp->next;
//		free(temp2->content);
//		free(temp2);
//	}
//	free(out);
//	free(new);
//}
//		if (lst->next)
//			created = ft_lstnew(f(lst->content));
//		else
//			created = NULL;
