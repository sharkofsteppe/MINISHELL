/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_ponctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:11:35 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/30 13:41:10 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/minishell.h"

void		disp(char *fmt, int i, int *ret)
{
	if (fmt[i] == '>' && fmt[i + 1] == '>' && *ret == 0)
		*ret = doublesym(&fmt[++i], '>', '>');
	if (fmt[i] == '>' && *ret == 0)
		*ret = doublesym(&fmt[i], '>', '<');
	if (fmt[i] == '>' && fmt[i + 1] != '>' && *ret == 0)
		*ret = doublesym(&fmt[i], '>', '>');
	if (fmt[i] == '<' && *ret == 0)
		*ret = doublesym(&fmt[i], '<', '<');
	if (fmt[i] == '<' && fmt[i + 1] == ' ' && *ret == 0)
		*ret = doublesym(&fmt[i], '<', '>');
}

int		doublerdr(char *fmt)
{
	int	i;
	int	ret;
	int	sig;

	i = 0;
	ret = 0;
	sig = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\\' && fmt[i + 1] != '\0')
			onepush(&i, &sig);
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt, &sig);
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', ';');
		if (sig == 0)
			i++;
		sig = 0;
	}
	return (ret);
}

int		doublerdrdeux(char *fmt)
{
	int	i;
	int	ret;
	int	sig;

	i = 0;
	ret = 0;
	sig = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\\' && fmt[i + 1] != '\0')
			onepush(&i, &sig);
		if (fmt[i] == '"' || fmt[i] == '\'')
			justuer(&i, fmt, &sig);
		if (fmt[i] == '>' && fmt[i + 1] == '>' && ret == 0)
			ret = doublesym(&fmt[++i], '>', '|');
		if (sig == 0)
			i++;
		sig = 0;
	}
	return (ret);
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
			g_shell.status = 1600;
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
			g_shell.status = 1601;
			*flag = 1;
			break ;
		}
		(*fmt)++;
	}
}
