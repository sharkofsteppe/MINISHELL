/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:26:39 by gesperan          #+#    #+#             */
/*   Updated: 2020/10/31 17:27:50 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	int		i;
	char	*newstring;

	i = 0;
	newstring = (char*)malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (newstring == NULL)
	{
		return (NULL);
	}
	while (source[i])
	{
		newstring[i] = source[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
