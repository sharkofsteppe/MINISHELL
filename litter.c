/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   litter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:44:24 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/31 17:45:08 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

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
