/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/30 13:50:13 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

int		put_int(int c)
{
	write(1, &c, 1);
	return (c);
}

int		check_term(int argc, char **argv, t_shell *shell)
{
	char	*type;
	char	buffer[MAXBUF];

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
		return (1);
	type = get_env("TERM", shell);
	if (type == NULL || tgetent(buffer, type) != 1)
	{
		ft_putendl_fd("Can not find TERM or termcap base", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int		readkey(void)
{
	char	buf[2];
	char	c;

	while (read(STDIN_FILENO, &c, 1) != 1)
		;
	if (c == '\e')
	{
		if (read(STDIN_FILENO, &buf[0], 1) != 1)
			return ('\e');
		if (read(STDIN_FILENO, &buf[1], 1) != 1)
			return ('\e');
		if (buf[0] == '[')
		{
			if (buf[1] == 'A')
				return (24);
			else if (buf[1] == 'B')
				return (25);
		}
	}
	return (c);
}

void	handle_backspace(t_shell *shell)
{
	int		len;

	len = ft_strlen(shell->buf);
	if (shell->buf[0] != '\0')
	{
		tputs(cursor_left, 1, put_int);
		tputs(delete_character, 1, put_int);
		shell->buf[len - 1] = '\0';
	}
}

void	handle_ctrld(char *c, t_shell *shell)
{
	if (shell->buf[0] == '\0')
	{
		ft_strlcpy(shell->buf, "exit", 5);
		*c = 10;
	}
}

void	clear_console(t_shell *shell)
{
	tputs(restore_cursor, 1, put_int);
	tputs(tigetstr("ed"), 1, put_int);
	ft_bzero(shell->buf, MAXBUF);
}

void	handle_key_up(t_shell *shell)
{
	if (shell->h_ind == 0)
		return ;
	clear_console(shell);
	ft_strlcpy(shell->buf, shell->history[--shell->h_ind], MAXBUF);
	ft_putstr_fd(shell->buf, STDOUT_FILENO);
}

void	handle_key_down(t_shell *shell)
{
	int	size;

	size = size_arr(shell->history);
	if (shell->h_ind == size)
	{
		clear_console(shell);
		return ;
	}
	if (shell->buf[0] != '\0')
	{
		clear_console(shell);
		ft_strlcpy(shell->buf, shell->history[shell->h_ind++], MAXBUF);
		ft_putstr_fd(shell->buf, STDOUT_FILENO);
	}
}

void	handle_keys(int key, char *c, t_shell *shell)
{
	if (key == 24)
		handle_key_up(shell);
	else if (key == 25)
		handle_key_down(shell);
	else if (key == 4)
		handle_ctrld(c, shell);
	else if (key == 127)
		handle_backspace(shell);
}

char	*readline(t_shell *shell)
{
	char	*line;
	char	c;
	int		key;

	line = NULL;
	print_promt();
	tputs(save_cursor, 1, put_int);
	ft_bzero(shell->buf, MAXBUF);
	while (1)
	{
		key = readkey();
		c = (char)key;
		if (ft_isprint(c) || c == '\n')
		{
			write(STDOUT_FILENO, &c, 1);
			if (c != '\n')
				ft_strlcat(shell->buf, &c, MAXBUF);
		}
		handle_keys(key, &c, shell);
		if (c == 10)
			break ;
	}
	line = ft_calloc(ft_strlen(shell->buf), sizeof(char) + 1);
	ft_strlcpy(line, shell->buf, MAXBUF);
	return (line);
}

void	turn_off(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->term);
	tcgetattr(STDIN_FILENO, &shell->rest);
	shell->term.c_lflag &= ~(ICANON | ECHO);
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
}

void	turn_on(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->rest);
}

char	**history_add(char **old, char *new_line, t_shell *shell)
{
	char	**new;
	int		count;
	int		i;

	shell->h_ind = 0;
	i = -1;
	count = 0;
	while (old[count] != NULL)
		count++;
	new = (char **)ft_calloc(count + 2, sizeof(char *));
	if (count == 0)
	{
		new[++i] = ft_strdup(new_line);
		shell->h_ind++;
	}
	else
	{
		while (++i < count)
		{
			new[i] = ft_strdup(old[i]);
			shell->h_ind++;
		}
		if (ft_strncmp(new[i - 1], new_line, ft_strlen(new_line) + 1) != 0)
		{
			new[i] = ft_strdup(new_line);
			shell->h_ind++;
		}
	}
	free_split(old);
	return (new);
}

void	add_to_history(char *line, t_shell *shell)
{
	if (line[0] == '\0')
		return ;
	if (!shell->history)
		shell->history = (char **)ft_calloc(1, sizeof(char *));
	shell->history = history_add(shell->history, line, shell);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	g_shell.status = 0;
	g_shell.env = NULL;
	g_shell.history = NULL;
	g_shell.h_ind = 0;
	init_envp(env, &g_shell.env);
	g_shell.status = check_term(argc, argv, &g_shell);
	g_shell.oldin = dup(STDIN_FILENO);
	g_shell.oldout = dup(STDOUT_FILENO);
	while (1)
	{
		turn_off(&g_shell);
		line = readline(&g_shell);
		add_to_history(line, &g_shell);
		turn_on(&g_shell);
		if (analysis(line) == 0)
			processing(line, &g_shell);
		else
			print_error("Some error", 0, 0, 0);
		free(line);
	}
	return (EXIT_SUCCESS);
}
