/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comanda_ponctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:52:20 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/30 13:37:39 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

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
