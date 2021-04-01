/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:01:48 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 17:02:27 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_rdr(int *fd1, int *fd2)
{
	if (*fd1 != -1)
	{
		close(*fd1);
		*fd1 = -1;
	}
	if (*fd2 != -1)
	{
		close(*fd2);
		*fd2 = -1;
	}
}

int		rdr_error(char *file)
{
	print_error("minibash: ", 0, file, 1);
	g_shell.status = 1;
	return (1);
}
