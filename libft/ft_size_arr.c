/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:13:33 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/15 15:44:38 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		size_arr(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**newarr(char **arr, char *str)
{
	char	**newarr;
	int		len;
	int		i;
	if (arr == NULL)
		len = 0;
	else
		len = size_arr(arr);
	if (!(newarr = (char **)ft_calloc(sizeof(char *), (len + 2))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		newarr[i] = ft_strdup(arr[i]);
		i++;
	}
	newarr[i] = ft_strdup(str);
	newarr[i + 1] = NULL;
	if (arr != NULL)
		ft_memory_free(arr, size_arr(arr));
	return (newarr);
}
