/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_ponctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:49:03 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/28 18:53:37 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

char	*dollarqarg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return (om_arg(str, tmp, p));
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
	free(p->dlr);
	p->dlr = 0;
	return (str);
}

char	*questarg(char *str, t_list *tmp, t_pt *p)
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
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str + 2);
}

char	*ecrqarg(char *str, t_pt *p)
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
