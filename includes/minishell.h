/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:16:02 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 16:38:47 by gesperan         ###   ########.fr       */
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
# include <sys/stat.h>
# include "libft.h"
# define RED "\x1b[31m"
# define GRE "\x1b[32m"
# define YEL "\x1b[33m"
# define BLU "\x1b[34m"
# define MAG "\x1b[35m"
# define CYA "\x1b[36m"
# define RES "\x1b[0m"
# define MAXBUF 9048
# define CD_CHDIR 0
# define CD_NOHOME 1
# define CD_NOOLDPWD 2
# define CD_GETCWD 3

int				iter;

typedef struct	s_pip
{
	int		input;
	pid_t	pid;
	int		status;
	int		fds[2];
}				t_pip;

typedef struct	s_exp
{
	char	*f;
	char	*name;
	int		i;
	int		err;
}				t_exp;

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
	int				b_ind;
	char			**history;
	int				h_ind;
	int				status;
	int				oldin;
	int				oldout;
	struct termios	rest;
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

char			**list_to_mass(t_envp *head);
int				get_argv_size(char **argv);
int				builtin_exit(char **argv, t_shell *shell);
char			**copy_env(char **envp);
void			init_envp(char **envp, t_envp **head);
void			envp_add_back(t_envp **envp, t_envp *new);
int				envpsize_2(t_envp *envp);
t_envp			*new_elem(char *name, char *content);
char			*wombo_combo(char *str1, char *str2, char *str3);
char			*get_env(char *name, t_shell *shell);
void			free_split(char **split);
void			print_promt(void);
void			print_error(char *error, char *ext, char *cmd, int flag);
int				set_env(char *name, char *new, t_shell *shell);
int				builtin_cd(char **argv, int size, t_shell *shell);
int				builtin_pwd(void);
int				builtin_env(t_shell *shell);
int				builtin_export(char **argv, t_shell *shell);
int				builtin_unset(char **argv, t_shell *shell);
int				builtin_echo(char **argv, int size, t_shell *shell);
int				check_env(char *name, t_shell *shell);
void			sort_envp(t_envp **envp);
void			envp_clear(t_envp **env, void (*del)(void*));
int				set_status(int err);
int				put_int(int c);

int				analysis(char *line);
int				rdractedeux(char *fmt);
int				checkrdr(char *fmt);
int				checkcolons(char *fmt);
int				checkquots(char *fmt);
void			justuer(int *i, char *fmt, int *sig);
int				findfirst(char *fmt);
int				findlast(char *fmt);
int				doublesym(char *fmt, char c, char k);
void			itiswhatitis(int ret);
void			squotsl(char **fmt, char c, int *flag);
void			squots(char **fmt, char c, int *flag);
int				doublerdr(char *fmt);
int				doublerdrdeux(char *fmt);
void			onepush(int *i, int *sig);
void			disp(char *fmt, int i, int *ret);

char			*comandas(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*qdeux(char *str, t_list *tmp, t_pt *p);
char			*qun(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*dollar(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*ecr(char *str, t_list *tmp);
int				dol_sym(char c);
char			*quest(char *str, t_list *tmp);
char			*ecrq(char *str, t_list *tmp);
void			lower(t_pt *p, t_list *tmp);

int				processing(char *line, t_shell *shell);
void			step_by_step(t_pt *p, t_list **head, t_shell *shell);
void			do_same(t_pt *p, t_list **head);
void			go_ahead(t_pt *p, t_list **head, t_shell *shell);
void			every_move(t_pt *p);
void			pusher(int i, t_pt *p);
void			skipperl(t_pt *p);
void			skipper(t_pt *p);
t_pt			*init_ptr(void);
void			goparty(t_list **head, t_pt *p, t_shell *shell);
void			sortout(t_list *tmp, t_pt *p, t_shell *shell);

char			*argumentas(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*qdeuxarg(char *str, t_list *tmp, t_pt *p);
char			*qarg(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*dollararg(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*ecrarg(char *str, t_list *tmp, t_pt *p);
int				stop_sym(char c);
char			*om_arg(char *str, t_list *tmp, t_pt *p);
void			rec_arg(char *str, t_list *tmp, t_pt *p);
void			rec_argq(char *str, t_list *tmp, t_pt *p);
char			*dollarqarg(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*questarg(char *str, t_list *tmp, t_pt *p);
char			*ecrqarg(char *str, t_pt *p);

char			*rdrdisperse(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*redirectas(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*questrdr(char *str, t_list *tmp, t_pt *p);
char			*qrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*qdeuxrdr(char *str, t_list *tmp, t_pt *p);
char			*ecrrdr(char *str, t_list *tmp, t_pt *p);
char			*ecrqrdr(char *str, t_pt *p);
char			*dollarrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell);
char			*om_handle(char *str, t_list *tmp, t_pt *p);
void			rec_strd(char *str, t_list *tmp, t_pt *p);
void			rec_str(char *str, t_list *tmp, t_pt *p);
char			*rec_sym(char *str, t_pt *p);
void			mover(char **fmt, int *sig);
void			moverr(int *i, int *sig);

void			run_pipeline(t_list **head, t_shell *shell);
int				run_cmd(t_list *head, t_shell *shell);
int				prep_rdr(t_list *tmp);
t_rdr			*new_rdr(char *file, int type, int flag);
void			rdr_add_back(t_rdr **rdr, t_rdr *new);
int				handle_rdr(t_list *tmp);
void			close_rdr(int *fd1, int *fd2);
int				rdr_error(char *file);
int				check_type_0(t_list *tmp, int *i);
int				check_type_1(t_list *tmp, int *i);
int				check_type_2(t_list *tmp, int *i);
void			rdr_clear(t_list **head, t_rdr **rdr, void (*del)(void*));
void			set_pwd_env(char *pwd, char *oldpwd, t_shell *shell);
t_envp			*new_elem(char *name, char *content);
void			init_envp(char **envp, t_envp **head);
char			**copy_env(char **envp);
int				set_env(char *name, char *new, t_shell *shell);
void			envp_clear(t_envp **env, void (*del)(void*));
int				envpsize_2(t_envp *envp);
int				envpsize(t_envp *envp);
int				check_name(char *name, int *err);
int				check_argv(char **argv, int i, int *err);
void			add_to_envp(char *name, t_shell *shell, char *fetch);
void			print_export_err(int *err, char *name);
void			add_to_envp1(int i, int *err, char **argv, t_shell *shell);
void			exec_pipe(t_list *cmd, t_shell *shell);
void			run_pipe_cmd(t_list *cmd, t_shell *shell, int input, int out);
void			run_pipeline(t_list **cmd, t_shell *shell);
char			*search_bin_err(char **split, char *line);
char			*search_bin(char *bin, t_shell *shell);
void			run_solo_cmd(t_list *cmd, t_shell *shell);
char			**add_cmd_to_arg(char **arg, char *cmd);
int				check_builtin(char *cmd);
int				run_builtin(char *cmd, char **argv, t_shell *shell);
int				rdr_error(char *file);
int				check_term(int argc, char **argv, t_shell *shell);
void			turn_off(t_shell *shell);
void			turn_on(t_shell *shell);
int				readkey(void);
void			handle_key_down(t_shell *shell);
void			handle_keys(int key, char *c, t_shell *shell);
void			handle_key_up(t_shell *shell);
void			clear_console(t_shell *shell);
void			handle_ctrld(char *c, t_shell *shell);
void			handle_backspace(t_shell *shell);
char			**history_add(char **old, char *new_line, t_shell *shell);
void			add_to_history(char *line, t_shell *shell);
char			*readline(t_shell *shell);
int				cmd_error(char *cmd);
void			child_int(int sig);
void			child_quit(int sig);
void			wait_pid(int *status, t_shell *shell);
#endif
