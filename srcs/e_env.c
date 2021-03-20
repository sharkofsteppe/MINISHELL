/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:46:22 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 16:26:32 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	envp_clear(t_envp **env, void (*del)(void*))
{
	t_envp *tmp;
	t_envp *begin;

	begin = *env;
	while (begin)
	{
		tmp = begin->next;
		if (del)
		{
			del(begin->name);
			del(begin->content);
		}
		free(begin);
		begin = tmp;
	}
	*env = NULL;
}

int		envpsize_2(t_envp *envp)
{
	t_envp	*tmp;
	int		count;

	if (!envp)
		return (0);
	count = 0;
	tmp = envp;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		count++;
	return (count);
}

int		envpsize(t_envp *envp)
{
	t_envp	*tmp;
	int		count;

	if (!envp)
		return (0);
	count = 0;
	tmp = envp;
	while (tmp->next)
	{
		if (tmp->content)
			count++;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		count++;
	return (count);
}

char	**list_to_mass(t_envp **head)
{
	t_envp	*env;
	char	**mass;
	char	*elem;
	int		i;

	i = 0;
	env = *head;
	if (!(mass = (char **)malloc(sizeof(char *) * (envpsize(env) + 1))))
		return (NULL);
	while (env)
	{
		if (env->content != NULL)
		{
			elem = wombo_combo(ft_strdup(env->name), "=", ft_strdup(env->content));
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

t_envp	*new_elem(char *name, char *content)
{
	t_envp	*new;

	if (!(new = (t_envp *)malloc(sizeof(*new))))
		return(NULL);
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
		name = ft_substr(envp[i], 0, ft_strlen(envp[i]) - ft_strlen(fetch + 1) - 1);
		envp_add_back(head, new_elem(ft_strdup(name), ft_strdup(fetch + 1)));
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
	if (!(copy = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while(envp[++i] != NULL)
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
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
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
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
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
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			ret = env->content;
		env = env->next;
	}
	return (ret);
}

int	builtin_env(t_shell *shell)
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
	return (0);
}
