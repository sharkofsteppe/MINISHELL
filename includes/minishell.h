/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:57:50 by ezachari          #+#    #+#             */
/*   Updated: 2021/02/24 19:42:02 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct  s_all
{
    char    **cmd;
    char    **env;
    char    *home;
}               t_all;

/*
** UTILS    ==========================================
** comment: сюда записываем функции которые будут полезны и при парсинге и при экзекуте
*/
int             free_split(char **split);
int             print_promt(t_all *all);
char            *get_env(char *str, char **env);
int             set_env(char *src, char *dist, char **env);
/*
** EXEC     ==========================================
** comment: сюда записываем функции связанные с экзекутом
*/
int             exec_cmd(t_all *all);
int             exec_exit(t_all *all);
int             exec_cd(t_all *all);
int             exec_env(t_all *all);
int             exec_echo(t_all *all);
int             exec_setenv(t_all *all);
int             exec_unsetenv(t_all *all);
/*
** PARSER   ==========================================
** comment: сюда записываем функции связанные с парсингом
*/
#endif