/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:57:51 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/24 15:33:37 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	handle_main(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.status = 1;
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		print_promt();
		signal(SIGINT, handle_main);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

void	handle_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		signal(SIGINT, handle_main);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		signal(SIGQUIT, handle_main);
	}
}
