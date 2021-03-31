/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:43:35 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 17:43:48 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*new_elem(char *name, char *content)
{
	t_envp	*new;

	if (!(new = (t_envp *)malloc(sizeof(*new))))
		return (NULL);
	new->content = content;
	new->name = name;
	new->next = NULL;
	return (new);
}

void	init_envp(char **envp, t_envp **head)
{
	char	*fetch;
	char	*name;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		fetch = ft_strchr(envp[i], '=');
		name = ft_substr(envp[i], 0, ft_strlen(envp[i]) -
		ft_strlen(fetch + 1) - 1);
		envp_add_back(head, new_elem(ft_strdup(name),
		ft_strdup(fetch + 1)));
		free(name);
	}
}

char	**copy_env(char **envp)
{
	char	**copy;
	int		size;
	int		i;

	i = -1;
	size = 0;
	while (envp[size] != NULL)
		size++;
	if (!(copy = (char **)malloc(sizeof(char *) *
	(size + 1))))
		return (NULL);
	while (envp[++i] != NULL)
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	return (copy);
}

int		set_env(char *name, char *new, t_shell *shell)
{
	t_envp	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->name, name,
		ft_strlen(name) + 1) == 0)
		{
			if (env->content)
				free(env->content);
			env->content = new;
		}
		env = env->next;
	}
	return (1);
}

int		check_env(char *name, t_shell *shell)
{
	t_envp	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->name, name,
		ft_strlen(name) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
