/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/20 14:55:01 by gesperan         ###   ########.fr       */
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
		ft_putendl_fd("syntax error near unexpected token", 1);
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
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', ';');
	}
	i = -1;
	while (fmt[++i])
	{
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
		ft_putendl_fd("syntax error near unexpected token", 1);
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
	if (c == '\\' || c == '\'' || c == '"' || c == '\0' || c == ' ')
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
		if (*str == '$')
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
	return (++str);
}



char	*comandas( char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;

	if (*str == '"')
		return (qun(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeux(++str, tmp, p));
	if (*str == '\\')
		return (ecr(str, tmp));
	if (*str == '$' && *(str + 1) != '\\')
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

char	*ecrqarg(char *str, t_list *tmp, t_pt *p)
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

char	*dollararg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
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

char	*qarg(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char *del;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqarg(str, tmp, p);
		if (*str == '$')
			str = dollararg(++str, tmp, p, shell);
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
	if (*str == '$')
		return (dollararg(++str, tmp, p, shell));
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	if (*str != '\0')
		str++;
	if ((*str == ' ' || *str == '\0') && *p->safe != '\0')
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
	return (str + 2);
}

char	*ecrqrdr(char *str, t_list *tmp, t_pt *p)
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

	if (*str == '\\' && *(str + 1) == '\0')
	{
		tmp->rdr = newarr(tmp->rdr, "ambiguous redirect");
		p->q += 1;
		return (str++);
	}
	// if (*str == '')
	return (++str);
}

char	*dollarrdr(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	char	*dlr;

	if (ft_isdigit(*str))
		str = om_handle(str, tmp, p);
	printf("|%s |!!\n", str);
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
	else
		p->safe = ft_strdup("");
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
			str = ecrqrdr(str, tmp, p);
		if (*str == '$')
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


char	*redirectas(char *str, t_list *tmp, t_pt *p, t_shell *shell)
{
	char	*del;
	if (*str == '"')
		return (qrdr(++str, tmp, p, shell));
	if (*str == '\'')
		return (qdeuxrdr(++str, tmp, p));
	if (*str == '\\')
		return (ecrrdr(str, tmp, p));
	if (*str == '$')
		return (dollarrdr(++str, tmp, p, shell));
	if (*str != ' ')
	{
		del = p->safe;
		p->safe = ft_joinsym(p->safe, *str);
		free(del);
		str++;
	}
	if ((*str != '>' && p->q == 0) ||
		((*str == ' ' || *str == '\0') && p->safe != NULL))
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
	printf("|%d|\n", p->q);

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
		if (p->cmd == 1 && *str != ' ' && !(rd_sym(*str)))
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

	tmp = *head;
	while (tmp)
	{
		sortout(tmp, p, shell);
		tmp = tmp->next;
	}
	tmp = *head;
	int i;
	int j;
	while (tmp)
	{
		printf("ЛИСТ НОМЕР %d:COMMAND |%s|\n",i, tmp->cmd);
		j = 0;
		while (j < size_arr(tmp->arg))
		{
			printf("TRUE ARG: |%s| ",tmp->arg[j]);
			j++;
		}
		j = 0;
		while (j < size_arr(tmp->rdr))
		{
			printf("\nREDIRECT ARG: |%s|\n",tmp->rdr[j]);
			j++;
		}
		printf("\n");
		tmp = tmp->next;
		i++;
	}
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
	int		flag;

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
	t_list 	*tmp;

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

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		loop;
	int		read;
	t_shell	shell;

	(void)argc;
	(void)argv;
	loop = 1;
	shell.env = NULL;
	init_envp(env, &shell.env);
	while (loop == 1)
	{
		read = get_next_line(0, &line);
		if (analysis(line) == 0)
			processing(line, &shell);
		else
			printf("SOMETHING WENT WRONG\n");
		free(line);
	}
	return (0);
}
