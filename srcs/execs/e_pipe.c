/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:41:51 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 23:57:59 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_last_pipe(t_list *cmd, t_shell *shell)
{
	char		*command;
	char		**env;

	if (prep_rdr(cmd) == 1)
		exit(EXIT_FAILURE);
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		exit(run_builtin(cmd->cmd, cmd->arg, shell));
	}
	else
	{
		command = search_bin(cmd->cmd, shell);
		if (command)
		{
			cmd->arg = add_cmd_to_arg(cmd->arg, command);
			free(command);
		}
		else
			cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		env = list_to_mass(shell->env);
		if (execve(cmd->arg[0], cmd->arg, env) == -1)
			exit(cmd_error(cmd->cmd));
	}
}

void	exec_pipe(t_list *cmd, t_shell *shell)
{
	char		*command;
	char		**env;

	if (prep_rdr(cmd) == 1)
		exit(EXIT_FAILURE);
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		exit(run_builtin(cmd->cmd, cmd->arg, shell));
	}
	else
	{
		command = search_bin(cmd->cmd, shell);
		if (command)
		{
			cmd->arg = add_cmd_to_arg(cmd->arg, command);
			free(command);
		}
		else
			cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		env = list_to_mass(shell->env);
		if (execve(cmd->arg[0], cmd->arg, env) == -1)
			exit(cmd_error(cmd->cmd));
	}
}

void	run_pipe_cmd(t_list *cmd, t_shell *shell, int input, int out)
{
	pid_t	pidc;
	int		status;
	
	pidc = fork();
	if (pidc < 0)
		exit(EXIT_FAILURE);
	if (pidc == 0)
	{
		if (input != STDIN_FILENO)
		{
			dup2(input, STDIN_FILENO);
			close(input);
		}
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		exec_pipe(cmd, shell);
	}
	waitpid(pidc, &status, 0);
}

void	run_pipeline(t_list **cmd, t_shell *shell)
{
	t_pip	t;
	int		status;

	signal(SIGINT, child_int);
	signal(SIGQUIT, child_quit);
	if ((t.pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (t.pid == 0)
	{
		t.input = 0;
		while ((*cmd) && (*cmd)->flag == 1)
		{
			pipe(t.fds);
			run_pipe_cmd(*cmd, shell, t.input, t.fds[1]);
			close(t.fds[1]);
			t.input = t.fds[0];
			*cmd = (*cmd)->next;
		}
		if (t.input != STDIN_FILENO && (*cmd)->fdin == -1)
			dup2(t.input, STDIN_FILENO);
		run_last_pipe(*cmd, shell);
		close_rdr(&(*cmd)->fdin, &(*cmd)->fdout);
	}
	wait_pid(&status, shell);
	while ((*cmd) && (*cmd)->flag != 2)
		*cmd = (*cmd)->next;
}

void	run_solo_cmd(t_list *cmd, t_shell *shell)
{
	char		*command;
	char		**env;

	command = search_bin(cmd->cmd, shell);
	if (command)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, command);
		free(command);
	}
	else
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
	env = list_to_mass(shell->env);
	if (execve(cmd->arg[0], cmd->arg, env) == -1)
		exit(cmd_error(cmd->cmd));
}
