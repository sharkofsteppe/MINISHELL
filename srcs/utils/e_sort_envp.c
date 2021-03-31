/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_sort_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:45:02 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 19:03:00 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_elems(char **elem01, char **elem02, char **elem11, char **elem12)
{
	*elem01 = *elem02;
	*elem11 = *elem12;
}

void	black_box(char **name, char **content, char **nname, char **ncontent)
{
	t_envp	tmp;

	tmp.name = *name;
	tmp.content = *content;
	swap_elems(name, nname, content, ncontent);
	swap_elems(nname, &tmp.name, ncontent, &tmp.content);
}

void	sort_envp1(t_envp **envp)
{
	t_envp	*env;

	env = *envp;
	while (env)
	{
		if (env->next)
		{
			if (env->name[0] == env->next->name[0])
			{
				if (env->name[1] > env->next->name[1])
					black_box(&env->name, &env->content,
					&env->next->name, &env->next->content);
			}
			else if (env->name[0] > env->next->name[0])
				black_box(&env->name, &env->content,
				&env->next->name, &env->next->content);
		}
		env = env->next;
	}
}

void	sort_envp(t_envp **envp)
{
	int		i;
	int		size;

	i = -1;
	size = envpsize_2(*envp);
	while (++i < size)
		sort_envp1(envp);
}
