/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:29:47 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/07 18:30:13 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		count;

	if (!lst)
	{
		return (0);
	}
	count = 0;
	tmp = lst;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
	{
		count++;
	}
	return (count);
}
