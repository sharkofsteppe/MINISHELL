/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:19:39 by ezachari          #+#    #+#             */
/*   Updated: 2021/02/24 19:51:13 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exec_cd(t_all *all)
{
    char    dir[FILENAME_MAX];
    char    *path;
    char    *cwd;
    
    cwd = getcwd(dir, sizeof(dir) - 1);
    path = all->home;
    printf("%s\n", path);
    if (chdir(path) == -1)
        perror("");
    set_env("OLDPWD", cwd, all->env);
    return (1);
}