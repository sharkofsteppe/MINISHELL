/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:45:41 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 18:38:24 by ezachari         ###   ########.fr       */
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

void	black_box_envp(char **argv, int *err, t_shell *shell)
{
	t_exp		t;

	t.i = 0;
	while (argv[++t.i] != NULL)
	{
		if (check_argv(argv, t.i, err) == EXIT_FAILURE)
			continue ;
		if (ft_strchr(argv[t.i], '=') != NULL)
		{
			t.name = ft_substr(argv[t.i], 0, ft_strlen(argv[t.i]) -
			ft_strlen(ft_strchr(argv[t.i], '=')));
			if (check_name(t.name, argv, t.i, err) == EXIT_FAILURE)
				continue ;
			add_to_envp(t.name, shell, ft_strchr(argv[t.i], '='));
		}
		else if (ft_strchr(argv[t.i], '=') == NULL)
			add_to_envp1(t.i, err, argv, shell);
	}
}

int		builtin_export(char **argv, t_shell *shell)
{
	t_exp	t;

	t.err = 0;
	if (get_argv_size(argv) == 1)
		export_no_argv(shell);
	else
		black_box_envp(argv, &t.err, shell);
	return (t.err);
}
