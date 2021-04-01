/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:01:27 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/01 20:50:32 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cont(t_list *tmp, char *filename, int flag)
{
	tmp->outfile = filename;
	tmp->out_type = flag;
}

void	fill_cont1(t_list *tmp, char *filename, int flag)
{
	tmp->infile = filename;
	tmp->out_type = flag;
}

int		chose_rdr(t_list *tmp)
{
	t_rdr	*tp;

	if (tmp->rdr_l)
	{
		tp = tmp->rdr_l;
		while (tp != NULL)
		{
			if (tp->type == 1)
				fill_cont(tmp, tp->filename, O_CREAT | O_WRONLY | O_APPEND);
			else if (tp->type == 2)
				fill_cont(tmp, tp->filename, O_CREAT | O_WRONLY | O_TRUNC);
			else if (tp->type == 3)
				fill_cont1(tmp, tp->filename, O_RDONLY);
			tp = tp->next;
		}
	}
	handle_rdr(tmp);
	return (EXIT_SUCCESS);
}

int		prep_rdr(t_list *tmp)
{
	int		i;

	i = 0;
	if (tmp->rdr)
	{
		while (tmp->rdr[i] != NULL)
		{
			if (ft_strncmp(">>", tmp->rdr[i], 3) == 0)
			{
				if (check_type_0(tmp, &i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (ft_strncmp(">", tmp->rdr[i], 2) == 0)
			{
				if (check_type_1(tmp, &i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (ft_strncmp("<", tmp->rdr[i], 2) == 0)
			{
				if (check_type_2(tmp, &i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
	}
	return (chose_rdr(tmp));
}
