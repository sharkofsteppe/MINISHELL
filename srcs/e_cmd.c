/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:51:43 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/26 01:26:11 by ezachari         ###   ########.fr       */
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
	return (g_signal);
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

void	rdr_add_back(t_rdr **rdr, t_rdr *new)
{
	t_rdr	*tmp;

	if (rdr && *rdr && new)
	{
		tmp = *rdr;
		if (tmp == NULL)
			*rdr = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	else
		*rdr = new;
}

t_rdr	*new_rdr(char *file, int type, int flag)
{
	t_rdr	*new;

	if (!(new = (t_rdr *)malloc(sizeof(*new))))
		return(NULL);
	new->filename = file;
	new->type = type;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void	chose_rdr(t_list *tmp)
{
	t_rdr	*tp;

	if (tmp->rdr_l)
	{
		tp = tmp->rdr_l;
		while (tp != NULL)
		{
			if (tp->type == 1)
				tmp->outfile = tp->filename;
			else if (tp->type == 2)
				tmp->outfile = tp->filename;
			else if (tp->type == 3)
				tmp->infile = tp->filename;
			tp = tp->next;
		}
	}
}

void	prep_rdr(t_list *tmp)
{
	int		i;

	i = 0;
	if (tmp->rdr)
	{
		while (tmp->rdr[i] != NULL)
		{
			if (ft_strncmp(">>", tmp->rdr[i], 3) == 0)
			{
				rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 1, 0));
				i += 2;
			}
			else if (ft_strncmp(">", tmp->rdr[i], 2) == 0)
			{
				rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 2, 0));
				i += 2;
			}
			else if (ft_strncmp("<", tmp->rdr[i], 2) == 0)
			{
				rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 3, 0));
				i += 2;
			}
		}
	}
}

int			run_last_pipe(t_list *cmd, t_shell *shell, int input)
{
	char		*command;
	char		**env;
	
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		return (run_builtin(cmd->cmd, cmd->arg, shell));
	}
	else
	{
		command = search_bin(cmd->cmd, shell);
		if (input != STDIN_FILENO)
			dup2(input, STDIN_FILENO);
		cmd->arg = add_cmd_to_arg(cmd->arg, command);
		env = list_to_mass(shell->env);
		printf("tmp cmd: %s size %d\n", command, cmd->flag);
		execve(command, cmd->arg, env);
		perror("execve");
		exit (1);
			// free_split(env);
			// free(command);
	}
}

int			exec_pipe(t_list *cmd, t_shell *shell)
{
	char		*command;
	char		**env;
	
	if (check_builtin(cmd->cmd) == 1)
	{
		cmd->arg = add_cmd_to_arg(cmd->arg, cmd->cmd);
		return (run_builtin(cmd->cmd, cmd->arg, shell));
	}
	else
	{
		command = search_bin(cmd->cmd, shell);
		cmd->arg = add_cmd_to_arg(cmd->arg, command);
		env = list_to_mass(shell->env);
		execve(command, cmd->arg, env);
		perror("execve");
		exit (1);
		// free_split(env);
		// free(command);
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
	// waitpid(pidc, &status, 0);
	return (pidc);
}

void		run_pipeline(t_list **head, t_shell *shell)
{
	int		size;
	int		input;
	pid_t	pid;
	int		status;
	int		fds[2];
	t_list	*tmp;

	tmp = *head;
	size = ft_lstsize(tmp);
	pid = fork();
	// while (tmp)
	// {
	// 		pipe(fds);
	// 		run_pipe_cmd(tmp, shell, input, fds[1]);
	// 		close(fds[1]);
	// 		input = fds[0];
	// 		// printf("addr %p tmp cmd: %s flag %d\n", tmp, tmp->cmd, tmp->flag);
	// 		tmp = tmp->next;
	// }
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		input = 0;
		while (tmp && tmp->flag != 2)
		{
			pipe(fds);
			run_pipe_cmd(tmp, shell, input, fds[1]);
			close(fds[1]);
			input = fds[0];
			printf("addr %p tmp cmd: %s flag %d\n", tmp, tmp->cmd, tmp->flag);
			tmp = tmp->next;
		}
		run_last_pipe(tmp, shell, input);
		exit (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
}

void		run_cmd(t_list **head, t_shell *shell)
{
	return ;
}