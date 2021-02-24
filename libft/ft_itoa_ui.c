/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:28:43 by gesperan          #+#    #+#             */
/*   Updated: 2020/12/16 18:07:45 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countoflen(unsigned int n)
{
	int i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char		*ft_itoa_ui(unsigned int n)
{
	char	*newstring;
	int		lenghtofn;

	lenghtofn = ft_countoflen(n);
	if (!(newstring = (char*)malloc(sizeof(char) * (lenghtofn + 1))))
		return (NULL);
	newstring[lenghtofn] = '\0';
	lenghtofn--;
	if (n == 0)
		newstring[0] = '0';
	while (n != 0)
	{
		newstring[lenghtofn] = n % 10 + '0';
		n /= 10;
		lenghtofn--;
	}
	return (newstring);
}
