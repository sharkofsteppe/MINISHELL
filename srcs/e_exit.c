/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:52 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/25 22:09:37 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exit_shell(t_shell *shell, int err)
{
	// if (shell->argv)
	// 	free_split(shell->argv);
	// if (shell->cmd)
	// 	free_cmd(shell->cmd);
	// if (shell->e_envp)
	// 	free_split(shell->e_envp);
	// if (shell->env)
	// 	free_envp(shell->env);
	// if (shell->envp)
	// 	free_split(shell->envp);
	exit(err);
}

int		builtin_exit(t_shell *shell, int flag)
{
	if (flag)
		ft_putendl_fd("exit", 1);
	exit_shell(shell, g_signal);
	return (1);
}
