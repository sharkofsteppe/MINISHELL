/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:25:50 by gesperan          #+#    #+#             */
/*   Updated: 2021/01/14 09:23:28 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fillstr(char c, int len)
{
	char	*newstring;
	int		i;

	i = 0;
	if (!(newstring = (char*)ft_calloc(sizeof(char), (len + 1))))
		return (NULL);
	while (i < len)
	{
		newstring[i] = c;
		i++;
	}
	return (newstring);
}
