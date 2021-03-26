/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:45:41 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/26 15:23:16 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*lst_copy(t_envp *envp)
{
	t_envp	*copy;
	t_envp	*new;

	copy = NULL;
	while (envp)
	{
		if (envp->content)
		{
			new = new_elem(ft_strdup(envp->name), ft_strdup(envp->content));
			envp_add_back(&copy, new);
			envp = envp->next;
		}
		else
		{
			new = new_elem(ft_strdup(envp->name), NULL);
			envp_add_back(&copy, new);
			envp = envp->next;
		}
	}
	return (copy);
}

void	export_no_argv(t_shell *shell)
{
	t_envp	*env;
	t_envp	*clear;

	env = lst_copy(shell->env);
	clear = env;
	sort_envp(&env);
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->name, 1);
		if (env->content)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->content, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
	}
	envp_clear(&clear, free);
}

// char	**add_empy_envp(t_shell *shell, char *name)
// {
// 	char **copy;

// 	return (copy);
// }

char	*wombo_combo(char *str1, char *str2, char *str3)
{
	char	*combo;
	char	*wombo;

	wombo = ft_strjoin(str1, str2);
	combo = ft_strjoin(wombo, str3);
	free(wombo);
	if (str1)
		free(str1);
	if (str3)
		free(str3);
	return (combo);
}

int		builtin_export(char **argv, t_shell *shell)
{
	char	*fetch;
	char	*name;
	int		size;
	int		i;

	i = 0;
	size = get_argv_size(argv);
	if (size == 1)
		export_no_argv(shell);
	else
	{
		while (argv[++i] != NULL)
		{
			if (!ft_isalpha(argv[i][0]) && argv[i][0] != '_')
			{
				print_error("minibash: export: ", ": not a valid identifier", argv[i], 0);
				continue ;
			}
			fetch = ft_strchr(argv[i], '=');
			if (fetch != NULL)
			{
				name = ft_substr(argv[i], 0, ft_strlen(argv[i]) - ft_strlen(fetch));
				if ((check_env(name, shell)) == 0)
					envp_add_back(&shell->env, new_elem(ft_strdup(name), ft_strdup(fetch + 1)));
				else if ((check_env(name, shell)) == 1)
					set_env(name, ft_strdup(fetch + 1), shell);
				free(name);
			}
			else if (fetch == NULL)
				if ((check_env(argv[i], shell)) == 0)
					envp_add_back(&shell->env, new_elem(ft_strdup(argv[i]), NULL));
		}
	}
	return (0);
}
