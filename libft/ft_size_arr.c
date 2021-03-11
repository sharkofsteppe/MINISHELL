/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:13:33 by gesperan          #+#    #+#             */
/*   Updated: 2021/03/11 17:14:15 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		size_arr(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**str_to_array(char **array, char *str)
{
	char 	**new_array;
	int		i;
	i = 0;
	while (array != NULL && array[i] != NULL)
		i++;
	if (!(new_array = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (array != NULL && array[i] != NULL)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = str;
	i++;
	new_array[i] = NULL;
	if (array != NULL)
		free(array);
	array = NULL;
	return (new_array);
}
