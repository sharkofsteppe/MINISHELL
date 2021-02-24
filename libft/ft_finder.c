/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:45:18 by gesperan          #+#    #+#             */
/*   Updated: 2021/01/15 11:45:46 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			finder(const char *str, const char c)
{
	int		column;

	column = 0;
	while (str[column] != '\0')
	{
		if (str[column] == c)
			return (column);
		column++;
	}
	return (FALSE);
}
