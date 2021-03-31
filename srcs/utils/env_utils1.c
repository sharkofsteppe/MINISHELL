/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:45:24 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 17:46:20 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
