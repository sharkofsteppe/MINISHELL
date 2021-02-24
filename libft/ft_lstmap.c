/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:16:49 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/08 18:17:38 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*first_dst;

	if (!lst)
		return (NULL);
	first_dst = NULL;
	while (lst)
	{
		new_list = ft_lstnew(lst->content);
		if (!new_list)
		{
			ft_lstclear(&first_dst, del);
			return (NULL);
		}
		new_list->content = f(lst->content);
		ft_lstadd_back(&first_dst, new_list);
		lst = lst->next;
	}
	return (first_dst);
}
