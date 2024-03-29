/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:38:23 by gesperan          #+#    #+#             */
/*   Updated: 2021/04/02 16:44:03 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*newstring;

	if (str1 == NULL)
		return (ft_strdup(str2));
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!(newstring = (char*)ft_calloc(sizeof(char), len1 + len2 + 1)))
		return (NULL);
	i = -1;
	while (++i < len1)
		newstring[i] = str1[i];
	j = -1;
	while (++j < len2)
	{
		newstring[i] = str2[j];
		i++;
	}
	return (newstring);
}

char	*ft_joinsym(char *str, char c)
{
	size_t	i;
	size_t	len;
	char	*newstr;

	if (str != 0)
		len = ft_strlen(str);
	else
		len = 0;
	if (!(newstr = (char *)ft_calloc(sizeof(char), len + 2)))
		return (NULL);
	i = 0;
	if (str != 0)
	{
		while (i < len)
		{
			newstr[i] = str[i];
			i++;
		}
		newstr[i] = c;
	}
	else
		newstr[i] = c;
	return (newstr);
}
