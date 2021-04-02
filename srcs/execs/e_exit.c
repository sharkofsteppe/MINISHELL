/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:52 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 16:45:59 by ezachari         ###   ########.fr       */
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

void	check_exit_arg(char *arg, t_shell *shell)
{
	int		i;
	char	*num;

	num = ": numeric argument required";
	i = 0;
	while (arg[i] != '\0')
	{
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '-')
			i++;
		while (ft_isdigit(arg[i]))
			i++;
		if ((!ft_isdigit(arg[i]) && arg[i] != '\0') || i > 19)
		{
			print_error("minibash: exit: ", num, arg, 0);
			exit_shell(shell, 255);
		}
	}
}

void	exit_shell_with_args(t_shell *shell, char **a, int count)
{
	unsigned char	err;
	int				i;

	i = 0;
	if (count > 2)
	{
		print_error("minibash: exit: ", "too many arguments", 0, 0);
		exit_shell(shell, 1);
	}
	check_exit_arg(a[1], shell);
	err = ft_atoi(a[1]);
	exit(err);
}

int		builtin_exit(char **argv, t_shell *shell)
{
	int		count;

	count = get_argv_size(argv);
	ft_putendl_fd("exit", 1);
	if (count > 1)
		exit_shell_with_args(shell, argv, count);
	else if (count == 1)
		exit_shell(shell, shell->status);
	return (EXIT_FAILURE);
}
