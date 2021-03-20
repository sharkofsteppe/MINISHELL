/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:35 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/15 18:09:16 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void		print_error(char *error, char *ext, char *cmd, int flag)
{
	ft_putstr_fd(error, STDERR_FILENO);
	if (flag)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (ext)
	{
		ft_putendl_fd(ext, STDERR_FILENO);
		return ;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
