/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:52 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/28 14:41:27 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit_shell(shell, 1);
	return (1);
}
