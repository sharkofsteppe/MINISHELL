/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:44:48 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 16:49:43 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		set_status(int err)
{
	g_status = err;
	return (err);
}

void	set_pwd(char *cwd, char *cwd1, t_shell *shell)
{
	set_env("OLDPWD", ft_strdup(cwd), shell);
	set_env("PWD", ft_strdup(cwd1), shell);
}

int		go_past(char *cwd1, char dir[], t_shell *shell)
{
	char	*oldpwd;
	char	*path;

	oldpwd = get_env("OLDPWD", shell);
	if (chdir(oldpwd) == -1)
	{
		print_error("cd: ", 0, 0, 1);
		return (1);
	}
	path = getcwd(dir, FILENAME_MAX - 1);
	set_pwd(cwd1, path, shell);
	builtin_pwd();
	return (0);
}

int		go_home(char *home, char *cwd1, t_shell *shell)
{
	if (chdir(home) == -1)
	{
		print_error("cd: ", 0, 0, 1);
		return (1);
	}
	set_pwd(cwd1, home, shell);
	return (0);
}
int		builtin_cd(char **argv, int size, t_shell *shell)
{
	char	*cwd1;
	char	dir[FILENAME_MAX];

	cwd1 = getcwd(dir, FILENAME_MAX - 1);
	if (size == 1)
		return (go_home(get_env("HOME", shell), cwd1, shell));
	else
	{
		if (ft_strncmp(argv[1], "~", 2) == 0)
			return (go_home(get_env("HOME", shell), cwd1, shell));
		else if (ft_strncmp(argv[1], "-", 2) == 0)
			return (go_past(cwd1, dir, shell));
		else if (chdir(argv[1]) == -1)
		{
			print_error("cd: ", 0, 0, 1);
			return (1);
		}
		set_pwd(cwd1, getcwd(dir, FILENAME_MAX - 1), shell);
	}
	return (0);
}
