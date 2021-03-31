/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:33:41 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/31 19:30:11 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rec_sym(char *str, t_pt *p)
{
	char	*del;

	if (p->q == 1 && (*str == '>' || *str == '<'))
		return (str);
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	str++;
	return (str);
}

void	rec_str(char *str, t_list *tmp, t_pt *p)
{
	if ((*(str + 1) == '\0' || *(str + 1) == ' ') && p->safe != NULL)
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
}

void	rec_strd(char *str, t_list *tmp, t_pt *p)
{
	if ((*str == '\0' || *str == ' ') && p->safe != NULL)
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
}

char	*om_handle(char *str, t_list *tmp, t_pt *p)
{
	if (*(str + 1) == ' ' || *(str + 1) == '\0')
	{
		tmp->rdr = newarr(tmp->rdr, "");
		p->q += 1;
		return (++str);
	}
	else
		return (str + 1);
}
