/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrponctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:34:04 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/28 16:36:57 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

char	*qrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqrdr(str, p);
		if (*str == '$' && *(str + 1) == '?')
			str = questrdr(str, tmp, p);
		if (*str == '$' && *(str + 1) != '\\')
			str = dollarrdr(++str, tmp, p, shell);
		if (*str == '"')
			break ;
		if (*str != '\\' && (*str != '$' && *(str + 1) != '?'))
		{
			del = p->safe;
			p->safe = ft_joinsym(p->safe, *str);
			free(del);
			str++;
		}
	}
	rec_str(str, tmp, p);
	return (++str);
}

char	*qdeuxrdr(char *str, t_list *tmp, t_pt *p)
{
	char *del;

	while (*str != '\'')
	{
		if (*str == '\'')
			break ;
		del = p->safe;
		p->safe = ft_joinsym(p->safe, *str);
		free(del);
		str++;
	}
	if ((*(str + 1) == '\0' || *(str + 1) == ' ') && p->safe != NULL)
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
	return (++str);
}

char	*ecrrdr(char *str, t_list *tmp, t_pt *p)
{
	char *sub;
	char *del;
	char *one;

	sub = ft_substr(str, 1, 1);
	del = sub;
	one = p->safe;
	p->safe = ft_joinsym(p->safe, *sub);
	free(one);
	free(sub);
	if (*(str + 2) == '\0' || *(str + 2) == ' ')
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
	return (str + 2);
}

char	*ecrqrdr(char *str, t_pt *p)
{
	char *sub;
	char *del;
	char *one;

	if (*(str + 1) == '\\' || *(str + 1) == '$' || *(str + 1) == '"')
		sub = ft_substr(str, 1, 1);
	else
		sub = ft_substr(str, 0, 2);
	del = sub;
	one = p->safe;
	p->safe = ft_strjoin(p->safe, sub);
	free(one);
	free(sub);
	return (str + 2);
}

char	*dollarrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return (om_handle(str, tmp, p));
	while (dol_sym(*str))
	{
		del = p->dlr;
		p->dlr = ft_joinsym(p->dlr, *str);
		free(del);
		str++;
	}
	del = p->safe;
	dlr = get_env(p->dlr, shell);
	if (dlr != NULL)
	{
		p->safe = ft_strjoin(p->safe, dlr);
		free(del);
	}
	rec_strd(str, tmp, p);
	free(p->dlr);
	p->dlr = 0;
	return (str);
}
