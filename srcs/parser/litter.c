/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   litter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:44:24 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/31 19:29:44 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mover(char **fmt, int *sig)
{
	if (*sig == 0)
		*fmt += 1;
	*sig = 0;
}

void	itiswhatitis(int ret)
{
	if (ret == 1)
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_shell.status = 258;
	}
}

void	moverr(int *i, int *sig)
{
	if (*sig == 0)
		*i += 1;
	*sig = 0;
}
