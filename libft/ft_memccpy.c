/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:59:18 by gesperan          #+#    #+#             */
/*   Updated: 2020/10/30 15:59:28 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*destination;
	unsigned char	*source;

	i = 0;
	destination = (unsigned char*)dst;
	source = (unsigned char*)src;
	while (i < n)
	{
		destination[i] = source[i];
		if (source[i] == (unsigned char)c)
		{
			return (destination + i + 1);
		}
		i++;
	}
	return (NULL);
}
