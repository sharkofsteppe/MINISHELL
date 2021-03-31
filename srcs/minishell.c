/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/31 19:24:51 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_gshell(void)
{
	g_shell.status = 0;
	g_shell.env = NULL;
	g_shell.history = NULL;
	g_shell.h_ind = 0;
	tcgetattr(STDIN_FILENO, &g_shell.rest);
	g_shell.oldin = dup(STDIN_FILENO);
	g_shell.oldout = dup(STDOUT_FILENO);
}

void	sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDIN_FILENO);
	print_promt();
	ft_bzero(g_shell.buf, MAXBUF);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	init_gshell();
	init_envp(env, &g_shell.env);
	g_shell.status = check_term(argc, argv, &g_shell);
	signal(SIGINT, sigint);
	while (1)
	{
		turn_off(&g_shell);
		line = readline(&g_shell);
		add_to_history(line, &g_shell);
		turn_on(&g_shell);
		if (analysis(line) == 0)
			processing(line, &g_shell);
		free(line);
	}
	return (EXIT_SUCCESS);
}
