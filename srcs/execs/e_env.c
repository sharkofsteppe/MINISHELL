/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:46:22 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 17:46:36 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_mass(t_envp *head)
{
	t_envp	*env;
	char	**mass;
	char	*elem;
	int		i;

	i = 0;
	env = head;
	if (!(mass = (char **)malloc(sizeof(char *) *
	(envpsize(env) + 1))))
		return (NULL);
	while (env)
	{
		if (env->content != NULL)
		{
			elem = wombo_combo(ft_strdup(env->name), "=",
			ft_strdup(env->content));
			mass[i++] = elem;
		}
		env = env->next;
	}
	mass[i] = NULL;
	return (mass);
}

void	envp_add_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (envp && *envp && new)
	{
		tmp = *envp;
		if (tmp == NULL)
			*envp = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	else
		*envp = new;
}

char	*get_env(char *name, t_shell *shell)
{
	t_envp	*env;
	char	*ret;

	ret = NULL;
	env = shell->env;
	if (!name)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, name,
		ft_strlen(name) + 1) == 0)
			ret = env->content;
		env = env->next;
	}
	return (ret);
}

int		builtin_env(t_shell *shell)
{
	t_envp	*env;

	env = shell->env;
	while (env)
	{
		if (env->content)
		{
			ft_putstr_fd(env->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(env->content, 1);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
