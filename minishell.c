/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/15 19:48:35 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

t_pt	*init_ptr(void)
{
	t_pt *ptr;

	if (!(ptr = (t_pt *)malloc(sizeof(t_pt) * 1)))
		return (0);
	ptr->copy = 0;
	ptr->fmt = 0;
	ptr->cut = 0;
	ptr->cmd = 0;
	ptr->opt = 0;
	ptr->q = 2;
	ptr->safe = 0;
	return (ptr);
}

void	squots(char **fmt, char c, int *flag)
{
	*fmt += 1;
	while (**fmt != c)
	{
		if (**fmt == '\\' && *(*fmt + 1) == '\\')
			(*fmt) += 2;
		if (**fmt == c)
			break ;
		if (**fmt == '\\' && *(*fmt + 1) == c)
			(*fmt) += 2;
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
			squots(&fmt, '\'', &flag);
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

	if (*(str + 1) == '\\')
		sub = ft_substr(str, 0, 1);
	else
		sub = ft_substr(str, 0, 2);
	del = sub;
	one = tmp->cmd;
	tmp->cmd = ft_strjoin(tmp->cmd, sub);
	free(one);
	free(sub);
	return (str + 2);
}

char	*quno(char *str, t_list *tmp, t_pt *p)
{
	char *del;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrq(str, tmp);
		if (*str == '"')
			break ;
		del = tmp->cmd;
		tmp->cmd = ft_joinsym(tmp->cmd, *str);
		free(del);
		str++;
	}
	return (++str);
}

char	*qdeux(char *str, t_list *tmp, t_pt *p)
{
	char *del;
	while (*str != '\'')
	{
		if (*str == '\\')
			str = ecr(str, tmp);
		if (*str == '\'')
			break ;
		del = tmp->cmd;
		tmp->cmd = ft_joinsym(tmp->cmd, *str);
		free(del);
		str++;
	}
	return (++str);
}

char	*comandas( char *str, t_list *tmp, t_pt *p)
{
	char	*del;
	if (*str == '"')
		return (quno(++str, tmp, p));
	if (*str == '\'')
		return (qdeux(++str, tmp, p));
	if (*str == '\\')
		return (ecr(str, tmp));
	if (*str == ' ')
		p->cmd = 1;
	del = tmp->cmd;
	tmp->cmd = ft_joinsym(tmp->cmd, *str);
	free(del);
	str++;
	return (str);
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
	return (str + 2);
}

char	*ecrqarg(char *str, t_list *tmp, t_pt *p)
{
	char *sub;
	char *del;
	char *one;

	if (*(str + 1) == '\\')
		sub = ft_substr(str, 0, 1);
	else
		sub = ft_substr(str, 0, 2);
	del = sub;
	one = p->safe;
	p->safe = ft_strjoin(p->safe, sub);
	free(one);
	free(sub);
	return (str + 2);
}



char	*qdeuxarg(char *str, t_list *tmp, t_pt *p)
{
	char *del;
	while (*str != '\'')
	{
		if (*str == '\\')
			str = ecr(str, tmp);
		if (*str == '\'')
			break ;
		del = p->safe;
		p->safe = ft_joinsym(p->safe, *str);
		free(del);
		str++;
	}
	return (++str);
}

char	*qarg(char *str, t_list *tmp, t_pt *p)
{
	char *del;
	while (*str != '"')
	{
		if (*str == '\\')
			str = ecrqarg(str, tmp, p);
		if (*str == '"')
			break ;
		del = p->safe;
		p->safe = ft_joinsym(p->safe, *str);
		free(del);
		str++;
	}
	return (++str);
}

char	*argumentas(char *str, t_list *tmp, t_pt *p)
{
	char	*del;
	if (*str == '"')
		return (qarg(++str, tmp, p));
	if (*str == '\'')
		return (qdeuxarg(++str, tmp, p));
	if (*str == '\\')
		return (ecrarg(str, tmp, p));
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	str++;
	if (*str == ' ' || *str == '\0')
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
	}
	return (str);
}

char	*argument_rdr(char *str, t_list *tmp, t_pt *p)
{
	char	*del;
	if (*str == '"')
		return (qarg(++str, tmp, p));
	if (*str == '\'')
		return (qdeuxarg(++str, tmp, p));
	if (*str == '\\')
		return (ecrarg(str, tmp, p));
	del = p->safe;
	p->safe = ft_joinsym(p->safe, *str);
	free(del);
	if (*str != ' ')
		str++;
	if ((*str != '>' && p->q == 0) || *str == '\0' || *str == ' ')
	{
		tmp->arg = newarr(tmp->arg, p->safe);
		free(p->safe);
		p->safe = NULL;
		p->q += 1;
	}
	return (str);
}

char	*rdrdisperse(char *str, t_list *tmp, t_pt *p)
{
	while (*str != '\0')
	{
		str = argument_rdr(str, tmp, p);
		if (p->q == 2)
		{
			str++;
			break;
		}
	}
	return (str);
}

void	sortout(t_list *tmp, t_pt *p)
{
	char	*str;
	str = (char *)tmp->content;
	while (*str != '\0')
	{
		if (*str == '>' || *str == '<')
		{
			p->q = 0;
			str = rdrdisperse(str, tmp, p);
		}

		if (p->cmd == 0 && p->q == 2)
		{
			printf("HELLO\n");
			str = comandas(str, tmp, p);
		}
		if (p->cmd == 1 && *str == ' ')
			str++;
		if (p->cmd == 1 && *str != ' ' && *str != '>')
			str = argumentas(str, tmp, p);
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


void	goparty(t_list **head, t_pt *p)
{
	t_list *tmp;

	tmp = *head;
	while (tmp)
	{
		sortout(tmp, p);
		tmp = tmp->next;
	}
}


void	go_ahead(t_pt *p, t_list **head)
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
	goparty(head, p);
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
	char c;

	c = *p->fmt;
	p->fmt += 1;
	p->cut += 1;
	while (*p->fmt != c)
	{
		p->fmt += 1;
		p->cut += 1;
		if (*p->fmt == '\\')
		{
			p->fmt += 2;
			p->cut += 2;
		}
	}
}

void	pusher(int i, t_pt *p)
{
	p->fmt += i;
	p->cut += i;
}


void	step_by_step(t_pt *p, t_list **head)
{
	char *newstr;
	t_list *tmp;
	int		flag;

	flag = 0;
	if (*p->fmt == '\'')
		skipper(p);
	if (*p->fmt == '"')
		skipper(p);
	if (*p->fmt == '\\')
	{
		flag = 1;
		pusher(2, p);
	}
	if (flag == 0)
		pusher(1, p);
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
		goparty(head, p);
	}
}

int		processing(char *line)
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
			go_ahead(p, &head);
		if (*p->fmt == '|')
			do_same(p, &head);
		else
			step_by_step(p, &head);
	}
	tmp = head;
	int i;
	int j;
	while (tmp)
	{
		printf("ЛИСТ НОМЕР %d:COMMAND %s\n",i, tmp->cmd);
		j = 0;
		while (j < size_arr(tmp->arg))
		{
			printf("АРГУМЕНТЫ ЛИСТА %d, %s\n", i, tmp->arg[j]);
			j++;
		}
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&head,free);
	free(p);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		loop;
	int		read;

	(void)argc;
	(void)argv;
	(void)env;
	loop = 1;
	while (loop == 1)
	{
		read = get_next_line(0, &line);
		if (analysis(line) == 0)
			processing(line);
		else
			printf("SOMETHING WENT WRONG\n");
		free(line);
	}

	return (0);
}
