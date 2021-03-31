/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_ponctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:05:28 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/31 20:03:40 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sortout(t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*str;

	str = (char *)tmp->content;
	while (*str != '\0')
	{
		if (*str == '>' || *str == '<')
		{
			p->q = 0;
			str = rdrdisperse(str, tmp, p, shell);
		}
		if (p->cmd == 0 && p->q == 2 && *str != ' ')
			str = comandas(str, tmp, p, shell);
		if (*str == ' ')
			str++;
		if (p->cmd == 1 && !(stop_sym(*str)))
			str = argumentas(str, tmp, p, shell);
	}
	p->cmd = 0;
}

void	reset(t_shell *shell)
{
	dup2(shell->oldin, STDIN_FILENO);
	dup2(shell->oldout, STDOUT_FILENO);
}

void	goparty(t_list **head, t_pt *p, t_shell *shell)
{
	t_list *tmp;

	tmp = *head;
	while (tmp)
	{
		sortout(tmp, p, shell);
		tmp = tmp->next;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (tmp->flag == 1)
				run_pipeline(&tmp, shell);
			else if (tmp->flag == 0)
				shell->status = run_cmd(tmp, shell);
			if (tmp)
				tmp = tmp->next;
			reset(shell);
		}
		if (tmp)
			tmp = tmp->next;
	}
	rdr_clear(head, &(*head)->rdr_l, free);
}
