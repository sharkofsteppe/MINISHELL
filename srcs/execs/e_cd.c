/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:44:48 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 15:18:13 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_cd_err(int err)
{
	if (err == CD_NOHOME)
		ft_putstr_fd("minibash: cd: HOME not set\n", STDERR_FILENO);
	else if (err == CD_CHDIR)
		print_error("minibash: cd: ", 0, 0, 1);
	else if (err == CD_NOOLDPWD)
		ft_putstr_fd("minibash: cd: OLDPWD not set\n", STDERR_FILENO);
	else if (err == CD_GETCWD)
		print_error("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: ", 0, 0, 1);
	return (EXIT_FAILURE);
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
		return (print_cd_err(CD_NOOLDPWD));
	if (chdir(path))
		return (print_cd_err(CD_CHDIR));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD));
	set_pwd_env(new, old, shell);
	builtin_pwd();
	return (EXIT_SUCCESS);
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
		return (print_cd_err(CD_NOHOME));
	if (chdir(path))
		return (print_cd_err(CD_CHDIR));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD));
	set_pwd_env(new, old, shell);
	return (EXIT_SUCCESS);
}

int		cd_argv(char **argv, t_shell *shell)
{
	char	old[FILENAME_MAX];
	char	new[FILENAME_MAX];

	ft_bzero(old, FILENAME_MAX);
	getcwd(old, FILENAME_MAX);
	if (chdir(argv[1]))
		return (print_cd_err(CD_CHDIR));
	ft_bzero(new, FILENAME_MAX);
	if (getcwd(new, FILENAME_MAX) == NULL)
		return (print_cd_err(CD_GETCWD));
	set_pwd_env(new, old, shell);
	return (EXIT_SUCCESS);
}

int		builtin_cd(char **argv, int size, t_shell *shell)
{
	if (size == 1)
		return (cd_home(shell));
	else if (ft_strncmp(argv[1], "~", 2) == 0)
		return (cd_home(shell));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		return (cd_oldpwd(shell));
	else
		return (cd_argv(argv, shell));
	return (EXIT_SUCCESS);
}
