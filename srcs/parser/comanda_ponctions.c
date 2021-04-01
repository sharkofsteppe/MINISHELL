/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comanda_ponctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:52:20 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/01 20:29:50 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	onepush(int *i, int *sig)
{
	(*i) += 2;
	(*sig) = 1;
}

int		dol_sym(char c)
{
	if (c == '\\' || c == '\'' || c == '"' || c == '\0' ||
		c == ' ' || c == '$' || c == '=')
		return (0);
	return (1);
}

void	lower(t_pt *p, t_list *tmp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(tmp->cmd);
	p->cmd = 1;
	while (i < len)
	{
		tmp->cmd[i] = ft_tolower(tmp->cmd[i]);
		i++;
	}
}

char	*ecrq(char *str, t_list *tmp)
{
	char *sub;
	char *del;
	char *one;

	if (*(str + 1) == '\\' || *(str + 1) == '$' || *(str + 1) == '"')
		sub = ft_substr(str, 1, 1);
	else
		sub = ft_substr(str, 0, 2);
	del = sub;
	one = tmp->cmd;
	tmp->cmd = ft_strjoin(tmp->cmd, sub);
	free(one);
	free(sub);
	return (str + 2);
}

char	*quest(char *str, t_list *tmp)
{
	char	*del;
	char	*new;

	new = ft_itoa(g_shell.status);
	del = tmp->cmd;
	tmp->cmd = ft_strjoin(tmp->cmd, new);
	free(new);
	free(del);
	return (str + 2);
}
