/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:54:08 by ezachari          #+#    #+#             */
/*   Updated: 2021/02/24 18:58:27 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exec_cmd(t_all *all)
{
    if (ft_strncmp(all->cmd[0], "exit", 5) == 0)
        return (exec_exit(all));
    else if (ft_strncmp(all->cmd[0], "cd", 3) == 0)
        return (exec_cd(all));
    // else if (ft_strncmp(all->cmd[0], "echo", 5) == 0)
    //     return (exec_echo(all));
    else if (ft_strncmp(all->cmd[0], "pwd", 4) == 0)
        return (exec_pwd(all));
    else if (ft_strncmp(all->cmd[0], "env", 4) == 0)
        return (exec_env(all));
    // else if (ft_strncmp(all->cmd[0], "setenv", 7) == 0)
    //     return (exec_setenv(all));
    // else if (ft_strncmp(all->cmd[0], "unsetenv", 9) == 0)
    //     return (exec_unsetenv(all));
    return (0);
}