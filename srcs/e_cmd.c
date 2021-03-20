/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:51:43 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 19:05:24 by ezachari         ###   ########.fr       */
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
		builtin_echo(argv, get_argv_size(argv), shell);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (builtin_export(argv, shell));
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		builtin_unset(argv, shell);
	return (g_status);
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

// int	spawn_proc(int in, int out, t_shell *shell, int i)
// {
// 	pid_t	pid;
// 	char	**args;
// 	args = (char **)malloc(sizeof(char *) * 2);
// 	args[0] = shell->argv[i];
// 	args[1] = NULL;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2(in, 0);
// 			close(in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2(out, 1);
// 			close(out);
// 		}
// 		execvp(shell->argv[i], args);
// 	}
// 	wait(&pid);
// 	return (pid);
// }
// // int	fork_pipe(int n, t_shell *shell)
// // {
// // 	pid_t	pid;
// // 	int		fd[2];
// // 	int		i;
// // 	int		in;
// // 	char	**args;
// // 	i = 0;
// // 	args = (char **)malloc(sizeof(char *) * 2);
// // 	args[0] = shell->argv[i];
// // 	args[1] = NULL;
// // 	in = 0;
// // 	pid = fork();
// // 	while (i < n - 1)
// // 	{
// // 		pipe(fd);
// // 		spawn_proc(in, fd[1], shell, i++);
// // 		close(fd[1]);
// // 		in = fd[0];
// // 	}
// // 	if (in != 0)
// // 		dup2(in, 0);
// // 	if (pid == 0)
// // 		execvp(shell->argv[i], args);
// // 	wait(&pid);
// // 	return (0);
// // }

int		wait_pid(pid_t pid)
{
	int		sig;
	int		stat;

	waitpid(pid, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		sig = WTERMSIG(stat);
		if (sig == SIGINT)
			return (130);
		if (sig == SIGQUIT)
			return (131);
	}
	return (WIFEXITED(stat));
}

char	**new_arr()
{
	char	**new;

	new = (char **)malloc(sizeof(char *));
	new[0] = NULL;
	return (new);
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
		arg = new_arr();
	size = get_argv_size(arg);
	new = (char **)malloc(sizeof(char *) * (size + 2));
	new[j++] = ft_strdup(cmd);
	while (arg[++i] != NULL)
			new[j++] = ft_strdup(arg[i]);
	new[j] = NULL;
	free_split(arg);
	return (new);
}

// int		run_pipe_cmd(int in, int out, t_list *tmp, t_shell *shell)
// {
// 	pid_t	pid;
// 	char	*cmd;

// 	if (check_builtin(tmp->cmd) == 1)
// 		return (run_builtin(tmp->cmd, tmp->arg, shell));
// 	cmd = search_bin(tmp->cmd, shell);
// 	tmp->arg = add_cmd_to_arg(tmp->arg, tmp->cmd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2(in, 0);
// 			close(in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2(out, 1);
// 			close(out);
// 		}
// 		execve(cmd, tmp->arg, list_to_mass(&shell->env));
// 	}
// 	return (wait_pid(pid));
// }

// int		run_pipe(t_list **tmp, t_shell *shell)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	int		in;
// 	char	*cmd;

// 	in = 0;
// 	while ((*tmp)->flag == 1)
// 	{
// 		pipe(fd);
// 		run_pipe_cmd(in, fd[1], *tmp, shell);
// 		close(fd[1]);
// 		in = fd[0];
// 		*tmp = (*tmp)->next;
// 	}
// 	if (in != 0)
// 		dup2(in, 0);
// 	cmd = search_bin((*tmp)->cmd, shell);
// 	(*tmp)->arg = add_cmd_to_arg((*tmp)->arg, (*tmp)->cmd);
// 	pid = fork();
// 	if (pid == 0)
// 		execve(cmd, (*tmp)->arg, list_to_mass(&shell->env));
// 	return (wait_pid(pid));
// }

int		run_cmd(t_list *tmp, t_shell *shell)
{
	pid_t	pid;
	char	*command;

	tmp->arg = add_cmd_to_arg(tmp->arg, tmp->cmd);
	reddirection(tmp->rdr, shell);
	if (check_builtin(tmp->cmd) == 1)
		return (run_builtin(tmp->cmd, tmp->arg, shell));
	command = search_bin(tmp->cmd, shell);
	pid = fork();
	// handle_child(SIGQUIT);
	if (pid == 0)
	{
		execve(command, tmp->arg, list_to_mass(&shell->env));
		print_error("minibash ", ": command not found", tmp->cmd, 0);
		exit(1);
	}
	else if (pid < 0)
		ft_putstr_fd("fork failed", STDERR_FILENO);
	free(command);
	return (wait_pid(pid));
}
