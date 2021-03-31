/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ter_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:15:01 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 19:15:06 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_off(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->term);
	shell->term.c_lflag &= ~(ICANON | ECHO);
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
}

void	turn_on(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->rest);
}
