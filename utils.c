/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:03:36 by ezachari          #+#    #+#             */
/*   Updated: 2021/02/24 19:52:00 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     free_split(char **split)
{
    int count;

    count = -1;
    while (split[++count] != NULL)
    {
        free(split[count]);
    }
    free(split);
    return (1);
}

int     print_promt(t_all *all)
{
    char    dir[FILENAME_MAX];
    char    *path;

    path = getcwd(dir, sizeof(dir) - 1);
    ft_putstr_fd(path, 1);
    ft_putstr_fd(GREEN" $>"RESET, 1);
}

char    *get_env(char *str, char **env)
{
    int     i;
    int     len;
    char    *res;

    res = NULL;
    len = ft_strlen(str);
    i = -1;
    while (env[++i])
    {
        if (ft_strncmp(str, env[i], len) == 0)
            return ((res = ft_strdup(&env[i][len + 1])));
    }
    return (res);
}

int     set_env(char *src, char *dist, char **env)
{
    int i;
    int len;
    int len2;

    len = ft_strlen(src);
    len2 = ft_strlen(dist);
    i = -1;
    while (env[++i])
    {
        if (ft_strncmp(src, env[i], len) == 0)
            ft_memcpy(&env[i][len + 1], dist, len2);
    }
    return (1);
}