/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:56:00 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/01 21:41:40 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checkquots(char *fmt)
{
	int	flag;
	int	sig;

	flag = 0;
	sig = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '\\' && *(fmt + 1) != '\0')
		{
			sig = 1;
			fmt += 2;
		}
		if (*fmt == '"')
		{
			squots(&fmt, '"', &flag);
			sig = 1;
		}
		if (*fmt == '\'')
		{
			squotsl(&fmt, '\'', &flag);
			sig = 1;
		}
		mover(&fmt, &sig);
	}
	return (flag);
}

int		checkcolons(char *fmt)
{
	char	c;

	c = findfirst(fmt);
	if (c == ';' || c == '|' || findlast(fmt) == '|' || doublesym(fmt, ';', ';')
		|| doublesym(fmt, '|', '|'))
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_shell.status = 258;
		return (1);
	}
	return (0);
}

int		checkrdr(char *fmt)
{
	int		i;
	int		ret;
	int		sig;

	i = 0;
	ret = 0;
	sig = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\\' && fmt[i + 1] != '\0')
			onepush(&i, &sig);
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt, &sig);
		disp(fmt, i, &ret);
		if (sig == 0)
			i++;
		sig = 0;
	}
	itiswhatitis(ret);
	return (ret);
}

int		rdractedeux(char *fmt)
{
	char	c;
	int		ret;

	ret = doublerdr(fmt);
	if (ret == 0)
		ret = doublerdrdeux(fmt);
	c = findlast(fmt);
	if (c == '<' || c == '>' || doublesym(fmt, '<', ';') ||
		doublesym(fmt, '<', '|') || doublesym(fmt, '>', ';') ||
		doublesym(fmt, '>', '|'))
		ret = 1;
	if (ret == 1)
	{
		ft_putendl_fd("syntax error near unexpected token", 1);
		g_shell.status = 258;
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
