/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:35 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 19:52:34 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_error(char *cmd)
{
	int		fd;
	DIR		*dir;
	int		err;

	fd = open(cmd, O_WRONLY);
	dir = opendir(cmd);
	if (ft_strchr(cmd, '/') == NULL)
		print_error("minibash: ", ": command not found", cmd, 0);
	else if (fd == -1 && dir == NULL)
		print_error("minibash: ", ": No such file or directory", cmd, 0);
	else if (fd == -1 && dir != NULL)
		print_error("minibash: ", ": is a directory", cmd, 0);
	else if (fd != -1 && dir == NULL)
		print_error("minibash: ", ": Permission denied", cmd, 0);
	if ((fd == -1 && dir == NULL) || ft_strchr(cmd, '/') == NULL)
		err = 127;
	else
		err = 126;
	if (dir)
		closedir(dir);
	if (fd != -1)
		close(fd);
	return (err);
}

void		print_error(char *error, char *ext, char *cmd, int flag)
{
	ft_putstr_fd(error, STDERR_FILENO);
	if (flag)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (ext)
	{
		ft_putendl_fd(ext, STDERR_FILENO);
		return ;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
