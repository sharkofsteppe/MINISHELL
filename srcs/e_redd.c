/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:01:27 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/27 12:47:28 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_rdr(t_list *tmp)
{
	if (tmp->infile)
	{
		tmp->fdin = open(tmp->infile, tmp->in_type, S_IRWXU);
		if (tmp->fdin == -1)
		{
			print_error("minibash: ", 0, tmp->infile, 1);
			g_signal = 1;
			return ;
		}
		dup2(tmp->fdin, STDIN_FILENO);
	}
	if (tmp->outfile)
	{
		tmp->fdout = open(tmp->outfile, tmp->out_type, S_IRWXU);
		if (tmp->fdout == -1)
		{
			print_error("minibash: ", 0, tmp->outfile, 1);
			g_signal = 1;
			return ;
		}
		dup2(tmp->fdout, STDOUT_FILENO);
	}
	if (tmp->fdin != -1)
		close(tmp->fdin);
	if (tmp->fdout != -1)
		close(tmp->fdout);
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
			{
				tmp->outfile = tp->filename;
				tmp->out_type = O_CREAT | O_WRONLY | O_APPEND;
			}
			else if (tp->type == 2)
			{
				tmp->outfile = tp->filename;
				tmp->out_type = O_CREAT | O_WRONLY | O_TRUNC;
			}
			else if (tp->type == 3)
			{
				tmp->infile = tp->filename;
				tmp->in_type = O_RDONLY;
			}
			tp = tp->next;
		}
	}
}

int		prep_rdr(t_list *tmp)
{
	int		i;
	int		fd;

	i = 0;
	if (tmp->rdr)
	{
		while (tmp->rdr[i] != NULL)
		{
			if (ft_strncmp(">>", tmp->rdr[i], 3) == 0)
			{
				fd = open(tmp->rdr[i + 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
				if (fd == -1)
				{
					print_error("minibash: ", 0, tmp->rdr[i + 1], 1);
					g_signal = 1;
					return (EXIT_FAILURE);
				}
				else
					rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 1, 0));
				i += 2;
				close(fd);
			}
			else if (ft_strncmp(">", tmp->rdr[i], 2) == 0)
			{
				fd = open(tmp->rdr[i + 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
				if (fd == -1)
				{
					print_error("minibash: ", 0, tmp->rdr[i + 1], 1);
					g_signal = 1;
					return (EXIT_FAILURE);
				}
				else
					rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 2, 0));
				i += 2;
				close(fd);
			}
			else if (ft_strncmp("<", tmp->rdr[i], 2) == 0)
			{
				fd = open(tmp->rdr[i + 1], O_RDONLY, S_IRWXU);
				if (fd == -1)
				{
					print_error("minibash: ", 0, tmp->rdr[i + 1], 1);
					g_signal = 1;
					return (EXIT_FAILURE);
				}
				else
					rdr_add_back(&tmp->rdr_l, new_rdr(tmp->rdr[i + 1], 3, 0));
				i += 2;
				close(fd);
			}
		}
	}
	chose_rdr(tmp);
	handle_rdr(tmp);
	return (EXIT_SUCCESS);
}
