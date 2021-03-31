/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:17:24 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 17:17:30 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd_env(char *pwd, char *oldpwd, t_shell *shell)
{
	if (pwd)
	{
		if (get_env("PWD", shell) == NULL)
			envp_add_back(&shell->env, new_elem(ft_strdup("PWD"),
			ft_strdup(pwd)));
		else
			set_env("PWD", ft_strdup(pwd), shell);
	}
	if (oldpwd)
	{
		if (get_env("OLDPWD", shell) == NULL)
			envp_add_back(&shell->env, new_elem(ft_strdup("OLDPWD"),
			ft_strdup(oldpwd)));
		else
			set_env("OLDPWD", ft_strdup(oldpwd), shell);
	}
}
