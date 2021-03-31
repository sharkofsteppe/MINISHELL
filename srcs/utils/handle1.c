/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:14:20 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 19:14:24 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_key_down(t_shell *shell)
{
	int	size;

	size = size_arr(shell->history);
	if (shell->h_ind == size)
	{
		clear_console(shell);
		return ;
	}
	if (shell->buf[0] != '\0')
	{
		clear_console(shell);
		ft_strlcpy(shell->buf, shell->history[shell->h_ind++], MAXBUF);
		ft_putstr_fd(shell->buf, STDOUT_FILENO);
	}
}

void	handle_keys(int key, char *c, t_shell *shell)
{
	if (key == 24)
		handle_key_up(shell);
	else if (key == 25)
		handle_key_down(shell);
	else if (key == 4)
		handle_ctrld(c, shell);
	else if (key == 127)
		handle_backspace(shell);
}
