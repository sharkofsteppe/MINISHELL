/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:45:59 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 16:26:39 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	*delcontent(t_envp *env)
{
	if (env->name)
	{
		free(env->name);
		env->name = NULL;
	}
	if (env->content)
	{
		free(env->content);
		env->content = NULL;
	}
}

void	envp_delone(t_envp *env)
{
	if (env)
	{
		if (env->content)
			free(env->content);
		if (env->name)
			free(env->name);
		free(env);
	}
}

void	del_envp(char *name, t_shell *shell)
{
	t_envp	*env;
	t_envp	*tmp;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
		{
			tmp->next = env->next;
			envp_delone(env);
			return ;
		}
		tmp = env;
		env = env->next;
	}
}

int		builtin_unset(char **argv, t_shell *shell)
{
	int		size;
	int		i;

	i = 0;
	size = get_argv_size(argv);
	if (size == 1)
		return (0);
	else
	{
		while (argv[++i] != NULL)
		{
			if (check_env(argv[i], shell) == 1)
				del_envp(argv[i], shell);
		}
	}
	return (0);
}
