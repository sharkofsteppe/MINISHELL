/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:03:45 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/08 15:04:30 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;
	t_list *begin;

	begin = *lst;
	while (begin)
	{
		tmp = begin->next;
		if (del)
			del(begin->content);
		free(begin);
		begin = tmp;
	}
	*lst = NULL;
}
