/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:57:34 by thdexmun          #+#    #+#             */
/*   Updated: 2026/07/27 15:39:59 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
//	printf("%s\n", (char *)ft_lstlast(*out)->content);
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
