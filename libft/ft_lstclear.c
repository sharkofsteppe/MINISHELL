/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:03:45 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/13 17:33:19 by gesperan         ###   ########.fr       */
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
		ft_memory_free(begin->arg, size_arr(begin->arg));
		if (del)
		{
			del(begin->cmd);
			del(begin->content);
		}
		free(begin);
		begin = tmp;
	}
	*lst = NULL;
}
