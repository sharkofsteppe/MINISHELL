/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comanda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:35:59 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/01 20:29:24 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ecr(char *str, t_list *tmp)
{
	char *sub;
	char *del;
	char *one;

	sub = ft_substr(str, 1, 1);
	del = sub;
	one = tmp->cmd;
	tmp->cmd = ft_joinsym(tmp->cmd, *sub);
	free(one);
	free(sub);
	return (str + 2);
}

char	*dollar(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return (++str);
	while (dol_sym(*str))
	{
		del = p->dlr;
		p->dlr = ft_joinsym(p->dlr, *str);
		free(del);
		str++;
	}
	del = tmp->cmd;
	dlr = get_env(p->dlr, shell);
	if (dlr != NULL)
	{
		tmp->cmd = ft_strjoin(tmp->cmd, dlr);
		free(del);
	}
	if (*str == ' ')
		lower(p, tmp);
	free(p->dlr);
	p->dlr = 0;
	return (str);
}

char	*qun(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char *del;

	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrq(str, tmp);
		if (*str == '$' && dol_sym(*(str + 1)))
			str = dollar(++str, tmp, p, shell);
		if (*str == '"')
			break ;
		if (*str != '\\')
		{
			del = tmp->cmd;
			tmp->cmd = ft_joinsym(tmp->cmd, *str);
			free(del);
			str++;
		}
	}
	if (*(str + 1) == ' ')
		lower(p, tmp);
	return (++str);
}

char	*qdeux(char *str, t_list *tmp, t_pt *p)
{
	char *del;

	while (*str != '\'')
	{
		if (*str == '\'')
			break ;
		del = tmp->cmd;
		tmp->cmd = ft_joinsym(tmp->cmd, *str);
		free(del);
		str++;
	}
	if (*(str + 1) == ' ')
		lower(p, tmp);
	return (++str);
}

char	*comandas(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	if (*str == '"')
		return (qun(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeux(++str, tmp, p));
	if (*str == '\\')
		return (ecr(str, tmp));
	if (*str == '$' && *(str + 1) == '?')
		return (quest(str, tmp));
	if (*str == '$' && dol_sym(*(str + 1)))
		return (dollar(++str, tmp, p, shell));
	del = tmp->cmd;
	tmp->cmd = ft_joinsym(tmp->cmd, *str);
	free(del);
	str++;
	if (*str == ' ' || *str == '>' || *str == '<' || *str == '\0')
		lower(p, tmp);
	return (str);
}
