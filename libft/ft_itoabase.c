/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:53:16 by gesperan          #+#    #+#             */
/*   Updated: 2020/12/16 18:50:56 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(size_t num)
{
	int count;

	count = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 16;
		count++;
	}
	return (count);
}

static char		ft_alphs(size_t i, size_t num)
{
	int elm;

	elm = num / i;
	if (elm == 10)
		return ('a');
	else if (elm == 11)
		return ('b');
	else if (elm == 12)
		return ('c');
	else if (elm == 13)
		return ('d');
	else if (elm == 14)
		return ('e');
	else if (elm == 15)
		return ('f');
	else
		return (num / i + '0');
}

static char		*ft_changer(int count, size_t i, size_t num, char *newstring)
{
	char *tmp;

	if (num == 0)
	{
		newstring[count++] = '0';
		newstring[count] = '\0';
		return (newstring);
	}
	while (num / i > 15)
		i *= 16;
	while (i /= 16 != 1)
	{
		newstring[count++] = ft_alphs(i, num);
		num %= i;
		i /= 16;
	}
	newstring[count] = '\0';
	if (ft_strlen(newstring) > 8)
	{
		tmp = newstring;
		newstring = ft_substr(newstring, count - 8, 8);
		free(tmp);
	}
	return (newstring);
}

char			*ft_itoa_base(size_t num)
{
	char	*newstring;
	int		count;
	size_t	i;

	i = 1;
	count = 0;
	if (!(newstring = (char*)malloc(sizeof(char) * ft_nbrlen(num) + 1)))
		return (0);
	return (ft_changer(count, i, num, newstring));
}
