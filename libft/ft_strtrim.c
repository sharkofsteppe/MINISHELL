/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:34:56 by gesperan          #+#    #+#             */
/*   Updated: 2020/11/03 18:35:02 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strtrim(char const *str, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*newstring;

	if (!str || !set)
		return (NULL);
	j = ft_strlen(str);
	i = 0;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	while (j && ft_strchr(set, str[j - 1]))
		j--;
	len = j - i < 0 ? 0 : j - i;
	if ((!(newstring = malloc(sizeof(char) * len + 1))))
		return (NULL);
	newstring[len] = 0;
	j = 0;
	while (j < len)
	{
		newstring[j] = str[i];
		j++;
		i++;
	}
	return (newstring);
}
