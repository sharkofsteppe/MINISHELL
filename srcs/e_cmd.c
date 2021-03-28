/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:51:43 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/28 14:41:57 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*search_bin_err(char **split, char *line)
{
	free_split(split);
	free(line);
	print_error("minibash: ", 0, 0, 1);
	return(NULL);
}

char	*search_bin(char *bin, t_shell *shell)
{
	t_bin			d;
	int				i;

	i = -1;
	if ((d.path = get_env("PATH", shell)) == NULL)
		return (NULL);
	d.res = NULL;
	d.search = ft_split(d.path, ':');
	while (d.search[++i] != NULL)
	{
		d.newpath = ft_strjoin(d.search[i], "/");
		if ((d.dir = opendir(d.newpath)) == NULL)
			return (search_bin_err(d.search, d.newpath));
		while ((d.info = readdir(d.dir)) != NULL)
			if (ft_strncmp(d.info->d_name, bin, ft_strlen(bin) + 1) == 0)
				d.res = ft_strjoin(d.newpath, bin);
		free(d.newpath);
		closedir(d.dir);
	}
	free_split(d.search);
	return (d.res);
}

int		run_builtin(char *cmd, char **argv, t_shell *shell)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (builtin_exit(shell, 1));
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		(builtin_cd(argv, get_argv_size(argv), shell));
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (builtin_env(shell));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (builtin_echo(argv, get_argv_size(argv), shell));
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (builtin_export(argv, shell));
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (builtin_unset(argv, shell));
	return (1);
}

int		check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return(1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return(1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return(1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return(1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return(1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return(1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return(1);
	return (0);
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

int			run_last_pipe(t_list *cmd, t_shell *shell, int input)
{
	char		*command;
	char		**env;

	if (prep_rdr(cmd) == 1)
		return (EXIT_FAILURE);
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		return (run_builtin(cmd->cmd, cmd->arg, shell));
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
		if (input != STDIN_FILENO)
			dup2(input, STDIN_FILENO);
		if (execve(cmd->arg[0], cmd->arg, env) == -1)
		{
			print_error("minibash: ", ": command not found", cmd->cmd, 0);
			printf("%d\n", errno);
			exit (1);
		}
	}
}

int			exec_pipe(t_list *cmd, t_shell *shell)
{
	char		*command;
	char		**env;

	if (prep_rdr(cmd) == 1)
		return (EXIT_FAILURE);
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		return (run_builtin(cmd->cmd, cmd->arg, shell));
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
		{
			print_error("minibash: ", " :command not found", cmd->cmd, 0);
			exit (1);
		}
	}
}

int		run_pipe_cmd(t_list *cmd, t_shell *shell, int input, int out)
{
	pid_t	pidc;
	int		status;

	pidc = fork();
	if (pidc < 0)
		printf("FORK FAILED\n");
	if (pidc == 0)
	{
		if (input != STDIN_FILENO)
		{
			dup2(input, STDIN_FILENO);
			close(input);
		}
		if (out != STDIN_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		exec_pipe(cmd, shell);
		exit(EXIT_FAILURE);
	}
	waitpid(pidc, &status, 0);
	return (pidc);
}

void		run_pipeline(t_list **cmd, t_shell *shell)
{
	int		input;
	pid_t	pid;
	int		status;
	int		fds[2];

	if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		input = 0;
		while ((*cmd) && (*cmd)->flag == 1)
		{
			pipe(fds);
			run_pipe_cmd(*cmd, shell, input, fds[1]);
			close(fds[1]);
			input = fds[0];
			*cmd = (*cmd)->next;
		}
		run_last_pipe(*cmd, shell, input);
		exit (EXIT_FAILURE);
	}
	while ((*cmd) && (*cmd)->flag != 2)
		*cmd = (*cmd)->next;
	waitpid(pid, &status, 0);
}

int		run_solo_cmd(t_list *cmd, t_shell *shell)
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
	execve(cmd->arg[0], cmd->arg, env);
	print_error("minibash: ", ": command not found", cmd->cmd, 0);
	free_split(env);
}

int		run_cmd(t_list *tmp, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		check;

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
		{
			run_solo_cmd(tmp, shell);
			exit (EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
}
