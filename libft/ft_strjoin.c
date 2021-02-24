/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:38:23 by gesperan          #+#    #+#             */
/*   Updated: 2021/01/14 12:12:13 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	i;
	size_t	j;
	char	*newstring;

	i = 0;
	j = 0;
	if (!(str1) || !(str2))
		return (NULL);
	newstring = (char*)malloc(sizeof(newstring) *
	(ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!(newstring))
		return (NULL);
	while (i < ft_strlen(str1) + ft_strlen(str2) + 1)
	{
		if (i < ft_strlen(str1))
			newstring[i] = str1[i];
		if (i >= ft_strlen(str1))
		{
			newstring[i] = str2[j];
			j++;
		}
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
