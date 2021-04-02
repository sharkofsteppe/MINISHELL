/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:07:59 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 17:11:56 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_name(char *name, int *err)
{
	int		i;

	i = -1;
	while (name[++i] != '\0')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
		{
			free(name);
			*err = 1;
			print_error("minibash: export: ", ": \
			not a valid identifier", name, 0);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int		check_argv(char **argv, int i, int *err)
{
	if (!ft_isalpha(argv[i][0]) && argv[i][0] != '_')
	{
		*err = 1;
		print_error("minibash: export: ", ": \
		not a valid identifier", argv[i], 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	add_to_envp(char *name, t_shell *shell, char *fetch)
{
	if ((check_env(name, shell)) == 0)
		envp_add_back(&shell->env, new_elem(ft_strdup(name),
		ft_strdup(fetch + 1)));
	else if ((check_env(name, shell)) == 1)
		set_env(name, ft_strdup(fetch + 1), shell);
	free(name);
}

void	print_export_err(int *err, char *name)
{
	*err = 1;
	print_error("minibash: export: ", ": \
	not a valid identifier", name, 0);
}

void	add_to_envp1(int i, int *err, char **argv, t_shell *shell)
{
	if ((check_env(argv[i], shell)) == 0)
	{
		if (ft_strchr(argv[i], '+') == NULL)
		{
			envp_add_back(&shell->env,
			new_elem(ft_strdup(argv[i]), 0));
		}
		else
			print_export_err(err, argv[i]);
	}
}
