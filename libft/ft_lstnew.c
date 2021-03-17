/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:59:19 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/17 17:01:48 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	new->flag = 0;
	new->cmd = 0;
	new->arg = 0;
	new->rdr = 0;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstnew_pipe(void *content)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	new->content = content;
	new->flag = 1;
	new->arg = 0;
	new->rdr = 0;
	new->cmd = 0;
	new->next = NULL;
	return (new);
}
