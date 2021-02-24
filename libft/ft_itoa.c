/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:06:33 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/04 18:11:18 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countoflen(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		n *= -1;
		i = 1;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static int	ft_minint(int n, char *s)
{
	if (n == -2147483648)
	{
		s[1] = '2';
		n = -147483648;
	}
	return (n);
}

char		*ft_itoa(int n)
{
	char	*newstring;
	int		lenghtofn;

	lenghtofn = ft_countoflen(n);
	if (!(newstring = (char*)malloc(sizeof(char) * (lenghtofn + 1))))
		return (NULL);
	newstring[lenghtofn] = '\0';
	lenghtofn--;
	n = ft_minint(n, newstring);
	if (n < 0)
	{
		newstring[0] = '-';
		n = n * (-1);
	}
	else if (n == 0)
		newstring[0] = '0';
	while (n != 0)
	{
		newstring[lenghtofn] = n % 10 + '0';
		n /= 10;
		lenghtofn--;
	}
	return (newstring);
}
