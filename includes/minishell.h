/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:16:02 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/24 19:45:45 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <termcap.h>
# include <signal.h>
# include <term.h>
# include <stdio.h>
# include <dirent.h>
# include "libft.h"
# define RED "\x1b[31m"
# define GRE "\x1b[32m"
# define YEL "\x1b[33m"
# define BLU "\x1b[34m"
# define MAG "\x1b[35m"
# define CYA "\x1b[36m"
# define RES "\x1b[0m"
# define MAXBUF 9048

typedef struct	s_envp
{
	char			*name;
	char			*content;
	struct s_envp	*next;
}				t_envp;

typedef struct	s_cmd
{
	char	*name;
	char	**argv;
	int		argc;
	int		piped;
	int		redirected;
}				t_cmd;

typedef struct	s_shell
{
	char			buf[MAXBUF];
	int				ind;
	char			**history;
	int				index;
	int				status;
	pid_t			pid;
	struct termios	term;
	t_envp			*env;
}				t_shell;

typedef struct	s_bin
{
	char			*path;
	DIR				*dir;
	char			*newpath;
	char			**search;
	struct dirent	*info;
	char			*res;
}				t_bin;

typedef struct	s_sort
{
	char	*name;
	char	*tmpname;
	char	*content;
	char	*tmpcontent;
}				t_sort;

t_shell			g_shell;

char			**list_to_mass(t_envp **head);
int				get_argv_size(char **argv);
int				builtin_exit(t_shell *shell, int flag);
char			**copy_env(char **envp);
void			init_envp(char **envp, t_envp **head);
void			envp_add_back(t_envp **envp, t_envp *new);
t_envp			*new_elem(char *name, char *content);
char			*wombo_combo(char *str1, char *str2, char *str3);
char			*get_env(char *name, t_shell *shell);
void			free_split(char **split);
void			print_promt(void);
void			print_error(char *error, char *ext, char *cmd, int flag);
int				run_cmd(t_list *tmp, t_shell *shell);
int				set_env(char *name, char *new, t_shell *shell);
void			handle_main(int sig);
void			handle_child(int sig);
int				builtin_cd(char **argv, int size, t_shell *shell);
int				builtin_pwd(void);
int				builtin_env(t_shell *shell);
int				builtin_export(char **argv, t_shell *shell);
int				builtin_unset(char **argv, t_shell *shell);
int				builtin_echo(char **argv, int size, t_shell *shell);
int				check_env(char *name, t_shell *shell);
void			sort_envp(t_envp **envp);
int				envpsize_2(t_envp *envp);
void			envp_clear(t_envp **env, void (*del)(void*));
int				set_status(int err);
int				run_pipe(t_list **tmp, t_shell *shell);
void			reddirection(char **rdr, t_shell *shell);
int				put_int(int c);
#endif
