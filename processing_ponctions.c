/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_ponctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:05:28 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/28 20:09:04 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

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

void	goparty(t_list **head, t_pt *p, t_shell *shell)
{
	t_list *tmp;
	t_list *tmp1;

	tmp = *head;
	while (tmp)
	{
		sortout(tmp, p, shell);
		tmp = tmp->next;
	}
	tmp1 = *head;
	while (tmp1)
	{
		if (tmp1->cmd)
		{
			if (tmp1->flag == 1)
				run_pipeline(&tmp1, shell);
			else if (tmp1->flag == 0)
				run_cmd(tmp1, shell);
			if (tmp1)
				tmp1 = tmp1->next;
			dup2(shell->oldin, STDIN_FILENO);
			dup2(shell->oldout, STDOUT_FILENO);
		}
		if (tmp1)
			tmp1 = tmp1->next;
	}
	// if (tmp1->fdin != -1 && tmp1->fdin > 0)
	// 	close(tmp1->fdin);
	// if (tmp1->fdout != -1 && tmp1->fdout > 0)
	// 	close(tmp1->fdout);
	// tmp1 = *head;
	// int j;
	// while (tmp1)
	// {
	// 	printf("COMMAND |%s|\n", tmp1->cmd);
	// 	printf("FLAG |%d|\n", tmp1->flag);
	// 	j = 0;
	// 	while (j < size_arr(tmp1->arg))
	// 	{
	// 		printf("TRUE ARG :|%s|\n",tmp1->arg[j]);
	// 		j++;
	// 	}

	// 	j = 0;
	// 	while (j < size_arr(tmp1->rdr))
	// 	{
	// 		printf("\nREDIRECT ARG:|%s|\n",tmp1->rdr[j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	tmp1 = tmp1->next;
	// }
	ft_lstclear(head,free);
}
