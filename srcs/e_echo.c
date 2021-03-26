/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:07:29 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/26 15:23:00 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv, int size, t_shell *shell)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (size == 1)
		ft_putstr_fd("\n", 1);
	else
	{
		while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
		{
			flag = 1;
			i++;
		}
		while (argv[i] != NULL)
		{
			if (ft_strncmp(argv[i], "~", 2) == 0)
				ft_putstr_fd(get_env("HOME", shell), 1);
			else
				ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (!flag)
			ft_putchar_fd('\n', 1);
	}
	return (0);
}
