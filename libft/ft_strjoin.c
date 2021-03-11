/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:38:23 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/11 19:25:03 by gesperan         ###   ########.fr       */
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

char	*ft_joinsym(char *str, char c)
{
	size_t	i;
	size_t	len;
	char	*newstr;
	if (str != 0)
		len = ft_strlen(str);
	else
		len = 0;
	newstr = (char *)ft_calloc(sizeof(char), len + 2);
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
// "e"'c'\ho \-"n"
// gcc minishell.c libft.a -g -fsanitize=address
echo "hello \" world"
