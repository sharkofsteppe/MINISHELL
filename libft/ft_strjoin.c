/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:38:23 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/16 18:55:51 by gesperan         ###   ########.fr       */
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
	newstring = (char*)ft_calloc(sizeof(char), len1 + len2  + 1);
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
// echo "hello \" world"
