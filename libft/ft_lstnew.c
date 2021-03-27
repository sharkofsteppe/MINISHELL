/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:59:19 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/27 12:58:18 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	new->content = content;
	new->flag = 0;
	new->cmd = NULL;
	new->arg = NULL;
	new->rdr = NULL;
	new->fdpipe[0] = -1;
	new->fdpipe[1] = -1;
	new->fdin = -1;
	new->fdout = -1;
	new->rdr_l = NULL;
	new->outfile = NULL;
	new->infile = NULL;
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
	new->arg = NULL;
	new->rdr = NULL;
	new->cmd = NULL;
	new->fdpipe[0] = -1;
	new->fdpipe[1] = -1;
	new->fdin = -1;
	new->fdout = -1;
	new->rdr_l = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->next = NULL;
	return (new);
}
