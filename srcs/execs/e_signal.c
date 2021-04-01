/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:57:51 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 19:56:31 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_int(int sig)
{
	(void)sig;
	g_shell.status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	child_quit(int sig)
{
	g_shell.status = 131;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
