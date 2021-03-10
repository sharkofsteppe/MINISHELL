/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/10 19:43:21 by gesperan         ###   ########.fr       */
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
	ptr->storage = 0;
	return (ptr);
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
	}
}

void	pusher(int i, t_pt *p)
{
	p->fmt += i;
	p->cut += i;
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
	// checkcolons(fmt);
	// checkpipe(fmt);
	// tmp = *head;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->content);
	// 	tmp = tmp->next;
	// }
	return (0);
}


char	*compare(t_list *tmp, char *str, char *cstr)
{
	int	len;
	int	i;

	len = ft_strlen(cstr);
	i = ft_strncmp(str, cstr, len);
	if (i == 0)
	{
		tmp->cmd = ft_substr(str, 0, len - 1);
		return (str + len);
	}
	return (str);
}

char	*submaker(t_list *tmp, char *str)
{
	int		i;
	char	*begin;

	begin = str;
	i = 0;
	while (ft_isalnum(*str))
	{
		str++;
		i++;
	}
	tmp->cmd = ft_substr(begin, 0 , i);
	return (str);
}

char	*wcomanda(t_list *tmp, char *str)
{
	str = compare(tmp, str, "echo ");
	str = compare(tmp, str, "exit ");
	str = compare(tmp, str, "cd ");
	str = compare(tmp, str, "env ");
	str = compare(tmp, str, "pwd ");
	str = compare(tmp, str, "export ");
	str = compare(tmp, str, "unset ");
	if (tmp->cmd == 0)
		str = submaker(tmp, str);
	// printf("|%s|\n", str);
	return (str);
}
// char	*extractargs(t_list *tmp, char *str, char c)
// {
// 	int i;
// 	char *sub;

// 	sub = str + 1;
// 	i = 0;
// 	while (*(++str) != '"')
// 	{
// 		i++;
// 	}
// 	tmp->arg =
// 	return (str)
// }

char	*othersymbolas(t_list *tmp, char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		tmp->opt = ft_substr(str, 0, 2);
		return (str + 2);
	}
	// if (*str == '"')
	// {
	// 	str = extractargs(tmp, str, '"');

	// }
	return(str);
}

int		our_syms(char c)
{
	if (c == '\'' || c == '\\' || c == '"')
		return (1);
	else
		return (0);
}

char	*comandas(char *str, t_pt *p)
{
	int	push;

	push = 0;
	if (our_syms(*str))
	{
		push++;
	}
	if (ft_isalnum(*str))
	{
		printf("%s\n", p->storage);
		p->storage = ft_joinsym(p->storage, *str);
		push++;
	}
	return (str + push);
}
void	sortout(t_list *tmp, t_pt *p)
{
	char	*str;

	str = (char *)tmp->content;
	while (*str != '\0')
	{
		str = comandas(str, p);
		// if (ft_isalnum(*str))
		// 	str = wcomanda(tmp, str);

		// if (*str == ' ')
		// 	str++;

		// if (our_syms(*str))
		// 	str = othersymbolas(tmp, str);
	}
	printf("%s\n", p->storage);
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

void	step_by_step(t_pt *p, t_list **head)
{
	char *newstr;
	t_list *tmp;

	if (*p->fmt == '\'')
		skipper(p);
	if (*p->fmt == '"')
		skipper(p);
	if (*p->fmt == '\\')
		pusher(2, p);
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
	// tmp = head;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->cmd);
	// 	printf("%s\n", tmp->opt);
	// 	tmp = tmp->next;
	// }
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
