/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:37:14 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/07 18:38:01 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list *lastnode;

	if (!lst)
	{
		return (NULL);
	}
	lastnode = lst;
	while (lastnode->next)
		lastnode = lastnode->next;
	return (lastnode);
}
