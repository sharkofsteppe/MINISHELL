/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:47:06 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 19:01:40 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_rdr(t_list *tmp)
{
	if (tmp->infile)
	{
		tmp->fdin = open(tmp->infile, tmp->in_type, S_IRWXU);
		if (tmp->fdin == -1)
			return (rdr_error(tmp->infile));
		dup2(tmp->fdin, STDIN_FILENO);
	}
	if (tmp->outfile)
	{
		tmp->fdout = open(tmp->outfile, tmp->out_type, S_IRWXU);
		if (tmp->fdout == -1)
			return (rdr_error(tmp->outfile));
		dup2(tmp->fdout, STDOUT_FILENO);
	}
	close_rdr(tmp->fdin, tmp->fdout);
	return (EXIT_SUCCESS);
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
		return (NULL);
	new->filename = file;
	new->type = type;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void	rdr_clear(t_rdr **rdr, void (*del)(void*))
{
	t_rdr *tmp;
	t_rdr *begin;

	begin = *rdr;
	while (begin)
	{
		tmp = begin->next;
		if (del)
			del(begin->filename);
		free(begin);
		begin = tmp;
	}
	*rdr = NULL;
}
