/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:10:44 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/02 16:30:16 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			sig = 1;
			while (fmt[i] == ' ')
			{
				i++;
				if (fmt[i] == k)
					return (1);
			}
		}
		moverr(&i, &sig);
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

void	justuer(int *i, char *fmt, int *sig)
{
	char	c;
	int		interuption;

	c = fmt[*i];
	(*i)++;
	interuption = 0;
	while (fmt[*i] != c)
	{
		if (fmt[*i] == '\\' && c != '\'')
		{
			(*i) += 2;
			interuption = 1;
		}
		if (interuption == 0)
			(*i)++;
		interuption = 0;
	}
	(*i)++;
	(*sig) = 1;
}
