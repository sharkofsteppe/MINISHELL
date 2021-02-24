/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:10:25 by ezachari          #+#    #+#             */
/*   Updated: 2021/02/24 19:39:41 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exec_pwd(t_all *all)
{
    char    dir[FILENAME_MAX];
    char    *path;

    path = getcwd(dir, sizeof(dir) - 1);
    ft_putendl_fd(path, 1);
    return (1);
}