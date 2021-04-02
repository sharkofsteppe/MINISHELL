/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:34:41 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/02 16:11:19 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ecrarg(char *str, t_list *tmp, t_pt *p)
{
	char	*sub;
	char	*del;
	char	*one;

	sub = ft_substr(str, 1, 1);
	del = sub;
	one = p->safe;
	p->safe = ft_joinsym(p->safe, *sub);
	free(one);
	free(sub);
	if (*(str + 2) == '\0' || *(str + 2) == ' ')
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str + 2);
}

char	*dollararg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return (om_arg(str, tmp, p));
	while (dol_sym(*str))
	{
		printf("sdfg\n");
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
	rec_arg(str, tmp, p);
	free(p->dlr);
	p->dlr = 0;
	return (str);
}

char	*qarg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	iter = 0;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqarg(str, p);
		if (*str == '$' && *(str + 1) == '?')
			str = questarg(str, tmp, p);
		if (*str == '$' && dol_sym(*(str + 1)) && p->n == 0)
			str = dollarqarg(++str, tmp, p, shell);
		if (*str == '"')
			break ;
		if (*str != '\\' && p->n == 0)
		{
			del = p->safe;
			p->safe = ft_joinsym(p->safe, *str);
			free(del);
			str++;
		}
		p->n = 0;
	}
	rec_argq(str, tmp, p);
	return (++str);
}

char	*qdeuxarg(char *str, t_list *tmp, t_pt *p)
{
	char	*del;

	while (*str != '\'')
	{
		if (*str == '\'')
			break ;
		del = p->safe;
		p->safe = ft_joinsym(p->safe, *str);
		free(del);
		str++;
	}
	if (*(str + 1) == '\0' || *(str + 1) == ' ')
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (++str);
}

char	*argumentas(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	if (*str == '"')
		return (qarg(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeuxarg(++str, tmp, p));
	if (*str == '\\')
		return (ecrarg(str, tmp, p));
	if (*str == '$' && *(str + 1) == '?')
		return (questarg(str, tmp, p));
	if (*str == '$' && dol_sym(*(str + 1)))
		return (dollararg(++str, tmp, p, shell));
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	if (*str != '\0')
		str++;
	if (stop_sym(*str) && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str);
}
