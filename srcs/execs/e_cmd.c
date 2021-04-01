/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:51:43 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 20:54:32 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_builtin(char *cmd, char **argv, t_shell *shell)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (builtin_exit(argv, shell));
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (builtin_cd(argv, get_argv_size(argv), shell));
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (builtin_env(shell));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (builtin_echo(argv, get_argv_size(argv), shell));
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (builtin_export(argv, shell));
	else
		return (builtin_unset(argv, shell));
	return (127);
}

int		check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	wait_pid(int *status, t_shell *shell)
{
	wait(status);
	if (WIFEXITED(*status))
		shell->status = WEXITSTATUS(*status);
	waitpid(-1, status, 0);
}

char	**add_cmd_to_arg(char **arg, char *cmd)
{
	char	**new;
	int		size;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!arg)
		arg = (char **)ft_calloc(1, sizeof(char *));
	size = get_argv_size(arg);
	new = (char **)ft_calloc((size + 2), sizeof(char *));
	new[j++] = ft_strdup(cmd);
	while (arg[++i] != NULL)
		new[j++] = ft_strdup(arg[i]);
	new[j] = NULL;
	free_split(arg);
	return (new);
}

int		run_cmd(t_list *tmp, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		check;

	signal(SIGINT, child_int);
	signal(SIGQUIT, child_quit);
	if (prep_rdr(tmp) == 1)
		return (EXIT_FAILURE);
	check = check_builtin(tmp->cmd);
	if (check == 1)
	{
		tmp->arg = add_cmd_to_arg(tmp->arg, tmp->cmd);
		return (run_builtin(tmp->cmd, tmp->arg, shell));
	}
	else if (check == 0)
	{
		if ((pid = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
			run_solo_cmd(tmp, shell);
		wait_pid(&status, shell);
		close_rdr(tmp->infile, tmp->outfile);
	}
	return (shell->status);
}
