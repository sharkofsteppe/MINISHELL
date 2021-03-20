/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:45:23 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 16:26:49 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	builtin_pwd()
{
	char	dir[FILENAME_MAX];
	char	*cwd;

	cwd = getcwd(dir, FILENAME_MAX - 1);
	ft_putendl_fd(cwd, 1);
	return (0);
}
