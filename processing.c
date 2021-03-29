/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:56:08 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/28 20:07:29 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

void	go_ahead(t_pt *p, t_list **head, t_shell *shell)
{
	char	*newstr;
	t_list	*tmp;

	newstr = ft_substr(p->copy, 0, p->cut);
	tmp = ft_lstlast(*head);
	ft_lstadd_back(head, ft_lstnew(newstr));
	if (tmp != 0 && tmp->flag == 1)
	{
		tmp = ft_lstlast(*head);
		tmp->flag = 2;
	}
	p->cut = 0;
	if (*p->fmt != '\0')
		p->fmt += 1;
	p->copy = p->fmt;
	goparty(head, p, shell);
}

void	do_same(t_pt *p, t_list **head)
{
	char *newstr;

	newstr = ft_substr(p->copy, 0, p->cut);
	ft_lstadd_back(head, ft_lstnew_pipe(newstr));
	p->cut = 0;
	if (*p->fmt != '\0')
		p->fmt += 1;
	p->copy = p->fmt;
}

void	step_by_step(t_pt *p, t_list **head, t_shell *shell)
{
	char	*newstr;
	t_list	*tmp;

	every_move(p);
	if (*p->fmt == '\0')
	{
		newstr = ft_substr(p->copy, 0, p->cut);
		tmp = ft_lstlast(*head);
		ft_lstadd_back(head, ft_lstnew(newstr));
		if (tmp != 0 && tmp->flag == 1)
		{
			tmp = ft_lstlast(*head);
			tmp->flag = 2;
		}
		goparty(head, p, shell);
	}
}

int		processing(char *line, t_shell *shell)
{
	t_pt	*p;
	t_list	*head;

	p = init_ptr();
	p->fmt = line;
	p->copy = p->fmt;
	head = NULL;
	while (*p->fmt != '\0')
	{
		if (*p->fmt == ';')
			go_ahead(p, &head, shell);
		if (*p->fmt == '|')
			do_same(p, &head);
		else
			step_by_step(p, &head, shell);
	}
	free(p);
	return (0);
}
