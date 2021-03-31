/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:52 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 18:41:29 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *shell, int err)
{
	if (shell->history)
		free_split(shell->history);
	if (shell->env)
		envp_clear(&shell->env, free);
	exit(err);
}

void	exit_shell_with_args(t_shell *shell, char **argv)
{
	unsigned char	err;
	int				i;
	int				len;

	len = 0;
	i = -1;
	while (argv[1][++i] != '\0')
	{
		if (!ft_isdigit(argv[1][i]) || len >= 19)
		{
			print_error("minibash: exit:", ": \
			numeric argument required", argv[1], 0);
			exit_shell(shell, 255);
		}
		len++;
	}
	err = ft_atoi(argv[1]);
	exit(err);
}

int		builtin_exit(char **argv, t_shell *shell)
{
	int		count;

	count = get_argv_size(argv);
	ft_putendl_fd("exit", 1);
	if (count > 1)
		exit_shell_with_args(shell, argv);
	else if (count == 1)
		exit_shell(shell, shell->status);
	return (EXIT_FAILURE);
}
