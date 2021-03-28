/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:45:23 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/28 17:18:44 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd()
{
	char	dir[MAXBUF];

	ft_bzero(dir, sizeof(dir));
	getcwd(dir, sizeof(dir));
	ft_putendl_fd(dir, 1);
	return (0);
}
