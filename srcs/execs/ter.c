/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ter.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:13:09 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 14:30:11 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(1);
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
