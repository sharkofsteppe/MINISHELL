/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:13:46 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 14:30:21 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_backspace(t_shell *shell)
{
	int		len;

	len = ft_strlen(shell->buf);
	if (shell->buf[0] != '\0')
	{
		tputs(cursor_left, 1, put_int);
		tputs(delete_character, 1, put_int);
		shell->buf[len - 1] = '\0';
	}
}

void	handle_ctrld(char *c, t_shell *shell)
{
	if (shell->buf[0] == '\0')
	{
		ft_strlcpy(shell->buf, "exit", 5);
		*c = 10;
	}
}

void	clear_console(t_shell *shell)
{
	tputs(restore_cursor, 1, put_int);
	tputs(tigetstr("ed"), 1, put_int);
	ft_bzero(shell->buf, MAXBUF);
}

void	handle_key_up(t_shell *shell)
{
	if (shell->h_ind == 0)
		return ;
	clear_console(shell);
	ft_strlcpy(shell->buf, shell->history[--shell->h_ind], MAXBUF);
	ft_putstr_fd(shell->buf, STDOUT_FILENO);
}
