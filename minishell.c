/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/27 13:09:29 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

t_pt	*init_ptr(void)
{
	t_pt *ptr;

	if (!(ptr = (t_pt *)malloc(sizeof(t_pt) * 1)))
		return (0);
	ptr->copy = 0;
	ptr->fmt = 0;
	ptr->cut = 0;
	ptr->cmd = 0;
	ptr->q = 2;
	ptr->safe = 0;
	ptr->dlr = 0;
	return (ptr);
}

void	justuer(int *i, char *fmt)
{
	char	c;

	c = fmt[*i];
	(*i)++;
	while (fmt[*i] != c)
		(*i)++;
}


void	squots(char **fmt, char c, int *flag)
{
	int	interuption;

	*fmt += 1;
	interuption = 0;
	while (**fmt != c)
	{
		if (**fmt == '\\')
		{
			(*fmt) += 2;
			interuption = 1;
		}
		else if (**fmt == '\0')
		{
			ft_putendl_fd("syntax error: unclosed quotes", 1);
			g_signal = 1600;
			*flag = 1;
			break ;
		}
		if (interuption == 0)
			(*fmt)++;
		interuption = 0;
	}
}

void	squotsl(char **fmt, char c, int *flag)
{
	*fmt += 1;
	while (**fmt != c)
	{
		if (**fmt == '\0')
		{
			ft_putendl_fd("syntax error: unclosed quotes", 1);
			g_signal = 1601;
			*flag = 1;
			break ;
		}
		(*fmt)++;
	}
}

int		checkquots(char *fmt)
{
	int	flag;

	flag = 0;
	while(*fmt != '\0')
	{
		if (*fmt == '\\' && *(fmt + 1) != '\0')
			fmt += 2;
		if (*fmt == '"')
			squots(&fmt, '"', &flag);
		if (*fmt == '\'')
			squotsl(&fmt, '\'', &flag);
		fmt++;
	}
	return (flag);
}
int		findlast(char *fmt)
{
	int	i;

	i = ft_strlen(fmt);
	while (--i >= 0)
	{
		if (fmt[i] == ' ')
		{
			while (fmt[i] == ' ')
				i--;
		}
		if (fmt[i - 1] != '\\')
			return(fmt[i]);
		else
			return(fmt[i - 1]);
	}
	return (0);
}

int		findfirst(char *fmt)
{
	int i;

	i = 0;
	if (fmt[i] == ' ')
	{
		while (fmt[i] == ' ')
		{
			if (fmt[i] != ' ')
				return (fmt[i]);
			i++;
		}
	}
	return (fmt[i]);
}

int		doublesym(char *fmt, char c, char k)
{
	int	i;

	i = -1;
	while (fmt[++i])
	{
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt);
		if (fmt[i] == c)
		{
			i++;
			while (fmt[i] == ' ')
				i++;
			if (fmt[i] == k)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int		checkcolons(char *fmt)
{
	char	c;

	c = findfirst(fmt);
	if (c == ';' || c == '|' || findlast(fmt) == '|' || doublesym(fmt, ';', ';')
		|| doublesym(fmt, '|', '|'))
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_signal = 258;
		return (1);
	}
	return (0);
}



int		checkrdr(char *fmt)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (fmt[++i])
	{
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt);
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', '>');
		if (fmt[i] == '>' && ret == 0)
			ret = doublesym(&fmt[i], '>', '<');
		if (fmt[i] == '>' && fmt[i + 1] != '>' && ret == 0)
			ret = doublesym(&fmt[i], '>', '>');
		if (fmt[i] == '<' && ret == 0)
			ret = doublesym(&fmt[i], '<', '<');
		if (fmt[i] == '<' && fmt[i + 1] == ' ' && ret == 0)
			ret = doublesym(&fmt[i], '<', '>');
	}
	if (ret == 1)
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_signal = 258;
	}
	return (ret);
}

int		doublerdr(char *fmt)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (fmt[++i])
	{
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt);
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', ';');
	}
	i = -1;
	while (fmt[++i])
	{
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt);
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', '|');
	}
	return (ret);
}

int		rdractedeux(char *fmt)
{
	char	c;
	int		ret;

	ret = doublerdr(fmt);
	c = findlast(fmt);
	if (c == '<' || c == '>' || doublesym(fmt, '<', ';') ||
		doublesym(fmt, '<', '|') || doublesym(fmt, '>', ';') ||
		doublesym(fmt, '>', '|'))
		ret = 1;
	if (ret == 1)
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_signal = 258;
	}
	return (ret);
}

int		analysis(char *line)
{
	char	*fmt;

	fmt = line;
	if (checkquots(fmt))
		return (1);
	if (checkcolons(fmt))
		return (1);
	if (checkrdr(fmt))
		return (1);
	if (rdractedeux(fmt))
		return (1);
	return (0);
}

int		dol_sym(char c)
{
	if (c == '\\' || c == '\'' || c == '"' || c == '\0' || c == ' ' || c == '$')
		return (0);
	return (1);
}

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



char	*dollar(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return(++str);
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
		if (*str == '$' && *(str + 1) != '\\')
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
	return (++str);
}

char	*qdeux(char *str, t_list *tmp)
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
	return (++str);
}



char	*comandas( char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	// printf("%s\n", str);

	if (*str == '"')
		return (qun(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeux(++str, tmp));
	if (*str == '\\')
		return (ecr(str, tmp));
	if (*str == '$' && *(str + 1) != '\\' && *(str + 1) != '\0')
		return (dollar(++str, tmp, p, shell));
	del = tmp->cmd;
	tmp->cmd = ft_joinsym(tmp->cmd, *str);
	free(del);
	str++;
	if (*str == ' ' || *str == '>' || *str == '<')
		p->cmd = 1;
	return (str);
}



int		rd_sym(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}


char	*ecrarg(char *str, t_list *tmp, t_pt *p)
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

char	*om_arg(char *str, t_list *tmp, t_pt *p)
{
	if (*(str +1) == ' ' || *(str +1) == '\0')
	{
		tmp->arg = newarr(tmp->arg, "");
		p->q += 1;
		return (++str);
	}
	else
		return (str + 1);
}

char	*dollararg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return(om_arg(str, tmp, p));
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
	if ((*str == '\0' || *str == ' ') && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	free(p->dlr);
	p->dlr = 0;
	return (str);
}
char	*dollarqarg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		return(om_arg(str, tmp, p));
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

char	*qarg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char *del;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqarg(str, p);
		if (*str == '$' && *(str + 1) != '\\')
			str = dollarqarg(++str, tmp, p, shell);
		if (*str == '"')
			break ;
		if (*str != '\\')
		{
			del = p->safe;
			p->safe = ft_joinsym(p->safe, *str);
			free(del);
			str++;
		}
	}
	if ((*(str + 1) == '\0' || *(str + 1) == ' ') && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (++str);
}

char	*qdeuxarg(char *str, t_list *tmp, t_pt *p)
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
	if (*str == '$' && *(str + 1) != '\\')
		return (dollararg(++str, tmp, p, shell));
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	if (*str != '\0')
		str++;
	if ((*str == ' ' || *str == '\0' || *str == '>' || *str == '<') && p->safe != NULL)
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str);
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

char	*om_handle(char *str, t_list *tmp, t_pt *p)
{
	if (*(str +1) == ' ' || *(str +1) == '\0')
	{
		tmp->rdr = newarr(tmp->rdr, "");
		p->q += 1;
		return (++str);
	}
	else
		return (str + 1);
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
	if ((*str == '\0' || *str == ' ') && p->safe != NULL)
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
	free(p->dlr);
	p->dlr = 0;
	return (str);
}

char	*qrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char *del;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqrdr(str, p);
		if (*str == '$' && *(str + 1) != '\\')
			str = dollarrdr(++str, tmp, p, shell);
		if (*str == '"')
			break ;
		if (*str != '\\')
		{
			del = p->safe;
			p->safe = ft_joinsym(p->safe, *str);
			free(del);
			str++;
		}
	}
	if ((*(str + 1) == '\0' || *(str + 1) == ' ') && p->safe != NULL)
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
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
	if (*(str + 1) == '\0')
	{
		tmp->rdr = newarr(tmp->rdr, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (++str);
}

char	*rec_sym(char *str, t_pt *p)
{
	char	*del;
	if (p->q == 1 && (*str == '>' || *str == '<'))
		return (str);
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	str++;
	return (str);
}

char	*redirectas(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	if (*str == '"')
		return (qrdr(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeuxrdr(++str, tmp, p));
	if (*str == '\\')
		return (ecrrdr(str, tmp, p));
	if (*str == '$' && *(str + 1) != '\\')
		return (dollarrdr(++str, tmp, p, shell));
	if (*str != ' ')
		str = rec_sym(str, p);
	if ((*str != '>' && p->q == 0) ||
		((*str == ' ' || *str == '\0') && p->safe != NULL) || ((*str == '>' || *str == '<') && p->q == 1))
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
			break;
	}
	return (str);
}


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
		{
			str = comandas(str, tmp, p, shell);
		}
		if (*str == ' ')
		{
			str++;
		}
		if (p->cmd == 1 && *str != ' ' && !(rd_sym(*str)) && *str != '\0')
			str = argumentas(str, tmp, p, shell);
	}
	p->cmd = 0;
	// printf("|%s|\n", tmp->cmd);
	// int i = -1;
	// while (tmp->arg[++i])
	// {
	// 	printf("%d\n", i);
	// 	printf("%s\n", tmp->arg[i]);
	// }
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
			{
				run_pipeline(&tmp1, shell);
				break ;
			}
			else
				run_cmd(&tmp1, shell);
		}
		tmp1 = tmp1->next;
		if (tmp1)
		{
			if (tmp1->fdin != -1 && tmp1->fdin > 0)
				close(tmp1->fdin);
			if (tmp1->fdout != -1 && tmp1->fdout > 0)
				close(tmp1->fdout);
		}
		dup2(shell->oldin, STDIN_FILENO);
		dup2(shell->oldout, STDOUT_FILENO);
	}
	// tmp1 = *head;
	// int j;
	// while (tmp1)
	// {
	// 	printf("COMMAND |%s|\n", tmp1->cmd);
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

void	skipper(t_pt *p)
{
	char	c;
	int		flag;

	c = *p->fmt;
	p->fmt += 1;
	p->cut += 1;
	flag = 0;
	while (*p->fmt != c)
	{
		if (*p->fmt == '\\')
		{
			p->fmt += 2;
			p->cut += 2;
			flag = 1;
		}
		if (flag == 0)
		{
			p->fmt += 1;
			p->cut += 1;
		}
		flag = 0;
	}
}

void	skipperl(t_pt *p)
{
	char	c;

	c = *p->fmt;
	p->fmt += 1;
	p->cut += 1;
	while (*p->fmt != c)
	{
		p->fmt += 1;
		p->cut += 1;
	}
}

void	pusher(int i, t_pt *p)
{
	p->fmt += i;
	p->cut += i;
}

void	every_move(t_pt *p)
{
	int		flag;

	flag = 0;
	if (*p->fmt == '\'')
		skipperl(p);
	if (*p->fmt == '"')
		skipper(p);
	if (*p->fmt == '\\')
	{
		pusher(2, p);
		flag = 1;
	}
	if (flag == 0)
		pusher(1, p);
}

void	step_by_step(t_pt *p, t_list **head, t_shell *shell)
{
	char *newstr;
	t_list *tmp;

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
	// tmp = head;
	// int i;
	// int j;
	// while (tmp)
	// {
	// 	printf("ЛИСТ НОМЕР %d:COMMAND %s\n",i, tmp->cmd);
	// 	j = 0;
	// 	while (j < size_arr(tmp->arg))
	// 	{
	// 		printf("АРГУМЕНТЫ ЛИСТА %d, %s\n", i, tmp->arg[j]);
	// 		j++;
	// 	}
	// 	tmp = tmp->next;
	// 	i++;
	// }
	// ft_lstclear(&head,free);
	free(p);
	return (0);
}

// int		main(int argc, char **argv, char **env)
// {
// 	char	*line;
// 	t_shell	shell;

// 	(void)argc;
// 	(void)argv;
// 	shell.env = NULL;
// 	init_envp(env, &shell.env);
// 	while (1)
// 	{
// 		print_promt();
// 		get_next_line(0, &line);
// 		if (analysis(line) == 0)
// 			processing(line, &shell);
// 		else
// 			printf("SOMETHING WENT WRONG\n");
// 		free(line);
// 	}
// 	return (0);
// }

int		put_int(int c)
{
	write(1, &c, 1);
	return (c);
}

int		check_term(int argc, char **argv, t_shell *shell)
{
	char	*type;
	char	buffer[MAXBUF];

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
		return (1);
	type = get_env("TERM", shell);
	if (type == NULL || tgetent(buffer, type) != 1)
	{
		ft_putendl_fd("Can not find TERM or termcap base", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int		readkey(void)
{
	char	buf[2];
	char	c;

	while (read(STDIN_FILENO, &c, 1) != 1)
		;
	if (c == '\e')
	{
		if (read(STDIN_FILENO, &buf[0], 1) != 1)
			return ('\e');
		if (read(STDIN_FILENO, &buf[1], 1) != 1)
			return ('\e');
		if (buf[0] == '[')
		{
			if (buf[1] == 'A')
				return (24);
			else if (buf[1] == 'B')
				return (25);
			else if (buf[1] == 'C')
				ft_putstr_fd("\e[C", 1);
			else if (buf[1] == 'D')
				ft_putstr_fd("\e[D", 1);
		}
	}
	return (c);
}

void	handle_backspace(t_shell *shell)
{
	int		len;

	len = ft_strlen(shell->buf);
	if (shell->buf[0] != '\0')
	{
		tputs(cursor_left, 1, put_int);
		tputs(delete_character, 1, put_int);
		shell->buf[len - 1] = '\0';
		// shell->b_ind--;
	}
}

void	handle_ctrld(char *c, t_shell *shell)
{
	if (shell->buf[0] == '\0')
	{
		ft_strlcpy(shell->buf, "exit", 5);
		*c = 10;
	}
}

void	handle_ctrlc(t_shell *shell)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	print_promt();
	ft_bzero(shell->buf, MAXBUF);
}

void	clear_console(t_shell *shell)
{
	int	len;

	len = ft_strlen(shell->buf);
	while (len-- > 0)
		ft_putstr_fd("\b \b", 1);
	ft_bzero(shell->buf, MAXBUF);
}

void	handle_key_up(t_shell *shell)
{
	if (shell->h_ind == 0)
		return ;
	clear_console(shell);
	ft_strlcpy(shell->buf, shell->history[--shell->h_ind], MAXBUF);
	ft_putstr_fd(shell->buf, STDOUT_FILENO);
}

void	handle_key_down(t_shell *shell)
{
	int	size;

	size = size_arr(shell->history);
	if (shell->h_ind == size)
	{
		clear_console(shell);
		return ;
	}
	if (shell->buf[0] != '\0')
	{
		clear_console(shell);
		ft_strlcpy(shell->buf, shell->history[shell->h_ind++], MAXBUF);
		ft_putstr_fd(shell->buf, STDOUT_FILENO);
	}
}

void	handle_keys(int key, char *c, t_shell *shell)
{
	if (key == 24)
		handle_key_up(shell);
	else if (key == 25)
		handle_key_down(shell);
	else if (key == 3)
		handle_ctrlc(shell);
	else if (key == 4)
		handle_ctrld(c, shell);
	else if (key == 127)
		handle_backspace(shell);
}

char	*readline(t_shell *shell)
{
	char	*line;
	char	c;
	int		key;

	line = NULL;
	print_promt();
	ft_bzero(shell->buf, MAXBUF);
	while (1)
	{
		key = readkey();
		c = (char)key;
		if (ft_isprint(c) || c == '\n')
		{
			write(STDOUT_FILENO, &c, 1);
			if (c != '\n')
				ft_strlcat(shell->buf, &c, MAXBUF);
		}
		handle_keys(key, &c, shell);
		if (c == 10)
			break ;
	}
	line = ft_calloc(ft_strlen(shell->buf), 2);
	ft_strlcpy(line, shell->buf, MAXBUF);
	return (line);
}

void	turn_off(t_shell *shell)
{
	ft_bzero(&shell->term, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &shell->term);
	shell->term.c_lflag &= ~(ICANON | ECHO);
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
}

void	turn_on(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->term);
	shell->term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
}

char	**history_add(char **old, char *new_line, t_shell *shell)
{
	char	**new;
	int		count;
	int		i;

	shell->h_ind = 0;
	i = -1;
	count = 0;
	while (old[count] != NULL)
		count++;
	new = (char **)ft_calloc(count + 2, sizeof(char *));
	if (count == 0)
	{
		new[++i] = ft_strdup(new_line);
		shell->h_ind++;
	}
	else
	{
		while (++i < count)
		{
			new[i] = ft_strdup(old[i]);
			shell->h_ind++;
		}
		if (ft_strncmp(new[i - 1], new_line, ft_strlen(new_line) + 1) != 0)
		{
			new[i] = ft_strdup(new_line);
			shell->h_ind++;
		}
	}
	free_split(old);
	return (new);
}

void	add_to_history(char *line, t_shell *shell)
{
	if (line[0] == '\0')
		return ;
	if (!shell->history)
		shell->history = (char **)ft_calloc(1, sizeof(char *));
	shell->history = history_add(shell->history, line, shell);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_shell	shell;

	shell.status = 0;
	shell.env = NULL;
	shell.history = NULL;
	shell.h_ind = 0;
	init_envp(env, &shell.env);
	shell.status = check_term(argc, argv, &shell);
	shell.oldin = dup(STDIN_FILENO);
	shell.oldout = dup(STDOUT_FILENO);
	while (1)
	{
		turn_off(&shell);
		line = readline(&shell);
		add_to_history(line, &shell);
		turn_on(&shell);
		if (analysis(line) == 0)
			processing(line, &shell);
		else
			print_error("Some error", 0, 0, 0);
		free(line);
	}
	return (EXIT_SUCCESS);
}
