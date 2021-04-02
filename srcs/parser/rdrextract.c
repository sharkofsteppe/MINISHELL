/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrextract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:50:18 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/02 15:45:42 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*questrdr(char *str, t_list *tmp, t_pt *p)
{
	char	*del;
	char	*new;

	new = ft_itoa(g_shell.status);
	del = p->safe;
	p->safe = ft_strjoin(p->safe, new);
	free(new);
	free(del);
	if (*(str + 2) == '\0' || *(str + 2) == ' ')
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str + 2);
}

char	*redirectas(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	if (*str == '"')
		return (qrdr(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeuxrdr(++str, tmp, p));
	if (*str == '\\')
		return (ecrrdr(str, tmp, p));
	if (*str == '$' && *(str + 1) == '?')
		return (questrdr(str, tmp, p));
	if (*str == '$' && dol_sym(*(str + 1)))
		return (dollarrdr(++str, tmp, p, shell));
	if (*str != ' ')
		str = rec_sym(str, p);
	if ((*str != '>' && p->q == 0) ||
		((*str == ' ' || *str == '\0') && p->safe != NULL) ||
		((*str == '>' || *str == '<') && p->q == 1))
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
	return (str);
}

char	*rdrdisperse(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	while (*str != '\0')
	{
		str = redirectas(str, tmp, p, shell);
		if (*str == ' ')
			str++;
		if (p->q == 2)
			break ;
	}
	return (str);
}
