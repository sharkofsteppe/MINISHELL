/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:44:48 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/26 21:32:03 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd(char **argv, int size, t_shell *shell)
{
	char		dir[MAXBUF];
	char		*path;
	int			ret;
	char		*pwd;

	ft_bzero(dir, sizeof(dir));
	if (argv[1] == NULL)
		path = argv[0];
	else
		path = argv[1];
	if (argv && argv[1][0] == '-')
	{
		path = get_env("OLDPWD", shell);
		if (!path)
		{
			print_error("minibash: ", "cd: OLDPWD not set", 0, 0);
			return (EXIT_FAILURE);
		}
	}
	else if (!argv[1] || argv[1][0] == '~')
	{
		path = get_env("HOME", shell);
		if (!path)
		{
			print_error("minibash: ", "cd: HOME not set", 0, 0);
			return (EXIT_FAILURE);
		}
	}
	if (!getcwd(dir, MAXBUF))
	{
		print_error("minibash: cd: ", path, 0, 1);
		return (EXIT_FAILURE);
	}
	ret = chdir(path);
	if (!get_env("OLDPWD", shell))
		envp_add_back(&shell->env, new_elem(ft_strdup("OLDPWD"), ft_strdup(dir)));
	set_env("OLDPWD", ft_strdup(dir), shell);
	if (ret == 0)
		return (EXIT_SUCCESS);
	print_error("minibash: cd: ", path, 0, 1);
	return (EXIT_FAILURE);
}
