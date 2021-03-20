/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:44:09 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 14:49:43 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	my_free(char *arg1, char **arg2, char **arg3)
{
	if (arg1)
		free(arg1);
	if (arg2)
		free_split(arg2);
	if (arg3)
		free_split(arg3);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	init_envp(env, &shell.env);
	while (1)
	{
		print_promt();
		get_next_line(0, &line);
		if (analysis(line) == 0)
			processing(line, &shell);
		else
			printf("SOMETHING WENT WRONG\n");
		free(line);
	}
	return (0);
}
// int		main(int argc, char **argv, char **envp)
// {
// 	t_shell	shell;
// 	char	**cmd;
// 	char	*line;
// 	int		ret;
// 	int		size;
// 	int		i;
// 	(void)argv;
// 	(void)argc;
// 	shell.env = NULL;
// 	if (envp == NULL)
// 		ft_putendl_fd("envp is empty", STDERR_FILENO);
// 	else
// 		init_envp(envp, &shell.env);
// 	while (1)
// 	{
// 		handle_main(SIGINT);
// 		handle_main(SIGQUIT);
// 		print_promt();
// 		ret = get_next_line(0, &line);
// 		if (*line == '\0')
// 			continue ;
// 		if (!(cmd = ft_split(line, ' ')))
// 			continue ;
// 		size = get_argv_size(cmd);
// 		i = -1;
// 		shell.argv = (char **)malloc(sizeof(char *) * (size + 1));
// 		while (++i < size)
// 			shell.argv[i] = ft_strdup(cmd[i]);
// 		shell.argv[i] = NULL;
// 		g_status = run_cmd(cmd, shell.argv, &shell);
// 		my_free(line, cmd, shell.argv);
// 	}
// 	return (g_status);
// }
