/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:48:45 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/29 15:05:39 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

void	rec_argq(char *str, t_list *tmp, t_pt *p)
{
	if ((*(str + 1) == '\0' || *(str + 1) == ' ') && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
}

void	rec_arg(char *str, t_list *tmp, t_pt *p)
{
	if ((*str == '\0' || *str == ' ') && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
}

char	*om_arg(char *str, t_list *tmp, t_pt *p)
{
	if (*(str + 1) == ' ' || *(str + 1) == '\0')
	{
		tmp->arg = newarr(tmp->arg, "");
		p->q += 1;
		return (++str);
	}
	else
		return (str + 1);
}

int		stop_sym(char c)
{
	if (c == '<' || c == '>' || c == ' ' || c == '\0' || c == '>')
		return (1);
	return (0);
}
