/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:10:44 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/30 14:07:55 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

void	itiswhatitis(int ret)
{
	if (ret == 1)
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_shell.status = 258;
	}
}

int		doublesym(char *fmt, char c, char k)
{
	int	i;
	int	sig;

	i = 0;
	sig = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\\' && fmt[i + 1] != '\0')
			onepush(&i, &sig);
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt, &sig);
		if (fmt[i] == c)
		{
			i++;
			while (fmt[i] == ' ')
				i++;
			if (fmt[i] == k)
				return (1);
		}
		if (sig == 0)
			i++;
		sig = 0;
	}
	return (0);
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
			return (fmt[i]);
		else
			return (fmt[i - 1]);
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

void	onepush_1(char **fmt, int *sig)
{
	(*fmt) += 2;
	(*sig) = 1;
}

void	justuer(int *i, char *fmt, int *sig)
{
	char	c;
	int		flag;

	flag = 0;
	c = fmt[*i];
	while (fmt[*i] != c)
	{
		if (fmt[*i] == '\\' && fmt[*i + 1] != '\0' && !flag)
		{
			onepush_1(&fmt, sig);
			flag = 1;
		}
		(*i)++;
	}
}
