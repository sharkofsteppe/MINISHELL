/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:03:14 by gesperan          #+#    #+#             */
/*   Updated: 2020/12/16 18:07:49 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_nbrlen(unsigned long long n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static char					ft_alphs(unsigned long long i, unsigned long long n)
{
	int elm;

	elm = n / i;
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
		return (n / i + '0');
}

static char					*ft_changer(int count, unsigned long long i,
							unsigned long long n, char *newstring)
{
	if (n == 0)
	{
		newstring[count++] = '0';
		newstring[count] = '\0';
		return (newstring);
	}
	while (n / i > 15)
		i *= 16;
	while (i /= 16 != 1)
	{
		newstring[count++] = ft_alphs(i, n);
		n %= i;
		i /= 16;
	}
	newstring[count] = '\0';
	return (newstring);
}

char						*ft_itoa_ptr(unsigned long long n)
{
	unsigned long long	i;
	char				*newstring;
	int					count;

	i = 1;
	count = 2;
	if (!(newstring = (char*)malloc(sizeof(char) * ft_nbrlen(n) + 3)))
		return (0);
	newstring[0] = '0';
	newstring[1] = 'x';
	return (ft_changer(count, i, n, newstring));
}
