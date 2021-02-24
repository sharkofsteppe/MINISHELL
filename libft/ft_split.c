/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:40:34 by gesperan          #+#    #+#             */
/*   Updated: 2021/01/15 10:33:05 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_findtheword(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] == c)
		i++;
	return ((char*)&str[i]);
}

static	int		ft_countwords(const	char *str, char c)
{
	int i;
	int quantity;

	i = 0;
	quantity = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == 0 && str[i] != c) ||
		(i != 0 && str[i - 1] != c && str[i] == c))
		{
			quantity++;
		}
		i++;
	}
	return (quantity);
}

static size_t	ft_lenofword(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	return (i);
}

char			**ft_split(char const *str, char c)
{
	size_t	i;
	size_t	countwords;
	char	**array;

	if (!str)
		return (NULL);
	i = 0;
	countwords = ft_countwords(str, c);
	array = (char**)malloc(sizeof(char*) * (countwords + 1));
	if (!array)
		return (NULL);
	array[countwords] = NULL;
	while (i < countwords)
	{
		str = ft_findtheword(str, c);
		array[i] = ft_substr(str, 0, ft_lenofword(str, c));
		if (array[i] == NULL)
		{
			return (ft_memory_free(array, i));
		}
		i++;
		str = str + ft_lenofword(str, c);
	}
	return (array);
}
