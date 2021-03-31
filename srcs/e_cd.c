/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:44:48 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/30 13:26:06 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd_env(char *pwd, char *oldpwd, t_shell *shell)
{
	if (pwd)
	{
		if (get_env("PWD", shell) == NULL)
			envp_add_back(&shell->env, new_elem(ft_strdup("PWD"), ft_strdup(pwd)));
		else
			set_env("PWD", ft_strdup(pwd), shell);
	}
	if (oldpwd)
	{
		if (get_env("OLDPWD", shell) == NULL)
			envp_add_back(&shell->env, new_elem(ft_strdup("OLDPWD"), ft_strdup(oldpwd)));
		else
			set_env("OLDPWD", ft_strdup(oldpwd), shell);
	}
}

int		print_cd_err(int err, t_shell *shell)
{
	if (err == CD_NOHOME)
		ft_putstr_fd("minibash: cd: HOME not set\n", STDERR_FILENO);
	else if (err == CD_CHDIR)
		print_error("minibash: cd: ", 0, 0, 1);
	else if (err == CD_NOOLDPWD)
		ft_putstr_fd("minibash: cd: OLDPWD not set\n", STDERR_FILENO);
	else if (err == CD_GETCWD)
		print_error("cd: error retrieving current directory: getcwd: cannot access parent directories: ", 0, 0, 1);
	return (err);
}

int		cd_oldpwd(t_shell *shell)
{
	char	*path;
	char	old[FILENAME_MAX];
	char	new[FILENAME_MAX];

	ft_bzero(old, FILENAME_MAX);
	getcwd(old, FILENAME_MAX);
	path = get_env("OLDPWD", shell);
	if (!path)
		return (print_cd_err(CD_NOOLDPWD, shell));
	if (chdir(path))
		return (print_cd_err(CD_CHDIR, shell));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD, shell));
	set_pwd_env(new, old, shell);
}

int		cd_home(t_shell *shell)
{
	char	*path;
	char	old[FILENAME_MAX];
	char	new[FILENAME_MAX];

	ft_bzero(old, FILENAME_MAX);
	getcwd(old, FILENAME_MAX);
	path = get_env("HOME", shell);
	if (!path)
		return (print_cd_err(CD_NOHOME, shell));
	if (chdir(path))
		return (print_cd_err(CD_CHDIR, shell));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD, shell));
	set_pwd_env(new, old, shell);
}

int		cd_argv(char **argv, t_shell *shell)
{
	char	*path;
	char	old[FILENAME_MAX];
	char	new[FILENAME_MAX];

	ft_bzero(old, FILENAME_MAX);
	getcwd(old, FILENAME_MAX);
	if (chdir(argv[1]))
		return (print_cd_err(CD_CHDIR, shell));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD, shell));
	set_pwd_env(new, old, shell);
}

int		builtin_cd(char **argv, int size, t_shell *shell)
{
	shell->status = 0;
	if (size == 1)
		return (cd_home(shell));
	else if (ft_strncmp(argv[1], "~", 2) == 0)
		return (cd_home(shell));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		return (cd_oldpwd(shell));
	else
		return(cd_argv(argv, shell));
	return (EXIT_SUCCESS);
}
