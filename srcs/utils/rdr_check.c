/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:14:58 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 18:39:08 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_type_0(t_list *tmp, int *i)
{
	int		fd;

	fd = open(tmp->rdr[*i + 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		print_error("minibash: ", 0, tmp->rdr[*i + 1], 1);
		g_shell.status = 1;
		return (EXIT_FAILURE);
	}
	else
		rdr_add_back(&tmp->rdr_l,
		new_rdr(ft_strdup(tmp->rdr[*i + 1]), 1, 0));
	*i += 2;
	close(fd);
	return (EXIT_SUCCESS);
}

int		check_type_1(t_list *tmp, int *i)
{
	int		fd;

	fd = open(tmp->rdr[*i + 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		print_error("minibash: ", 0, tmp->rdr[*i + 1], 1);
		g_shell.status = 1;
		return (EXIT_FAILURE);
	}
	else
		rdr_add_back(&tmp->rdr_l,
		new_rdr(ft_strdup(tmp->rdr[*i + 1]), 2, 0));
	*i += 2;
	close(fd);
	return (EXIT_SUCCESS);
}

int		check_type_2(t_list *tmp, int *i)
{
	int		fd;

	fd = open(tmp->rdr[*i + 1], O_RDONLY, S_IRWXU);
	if (fd == -1)
	{
		print_error("minibash: ", 0, tmp->rdr[*i + 1], 1);
		g_shell.status = 1;
		return (EXIT_FAILURE);
	}
	else
		rdr_add_back(&tmp->rdr_l,
		new_rdr(ft_strdup(tmp->rdr[*i + 1]), 3, 0));
	(*i) += 2;
	close(fd);
	return (EXIT_SUCCESS);
}
