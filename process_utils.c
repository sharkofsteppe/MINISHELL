/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:59:07 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/28 20:07:26 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

t_pt	*init_ptr(void)
{
	t_pt *ptr;

	if (!(ptr = (t_pt *)malloc(sizeof(t_pt) * 1)))
		return (0);
	ptr->copy = 0;
	ptr->fmt = 0;
	ptr->cut = 0;
	ptr->cmd = 0;
	ptr->q = 2;
	ptr->safe = 0;
	ptr->dlr = 0;
	return (ptr);
}

void	skipper(t_pt *p)
{
	char	c;
	int		flag;

	c = *p->fmt;
	p->fmt += 1;
	p->cut += 1;
	flag = 0;
	while (*p->fmt != c)
	{
		if (*p->fmt == '\\')
		{
			p->fmt += 2;
			p->cut += 2;
			flag = 1;
		}
		if (flag == 0)
		{
			p->fmt += 1;
			p->cut += 1;
		}
		flag = 0;
	}
}

void	skipperl(t_pt *p)
{
	char	c;

	c = *p->fmt;
	p->fmt += 1;
	p->cut += 1;
	while (*p->fmt != c)
	{
		p->fmt += 1;
		p->cut += 1;
	}
}

void	pusher(int i, t_pt *p)
{
	p->fmt += i;
	p->cut += i;
}

void	every_move(t_pt *p)
{
	int		flag;

	flag = 0;
	if (*p->fmt == '\'')
		skipperl(p);
	if (*p->fmt == '"')
		skipper(p);
	if (*p->fmt == '\\')
	{
		pusher(2, p);
		flag = 1;
	}
	if (flag == 0)
		pusher(1, p);
}
