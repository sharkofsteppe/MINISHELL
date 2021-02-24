/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:01:18 by gesperan          #+#    #+#             */
/*   Updated: 2020/10/28 19:34:06 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t lenghtdst;
	size_t i;

	lenghtdst = ft_strlen(dst);
	i = 0;
	if (dstsize <= lenghtdst)
	{
		return (dstsize + ft_strlen(src));
	}
	while (src[i] && i < dstsize - lenghtdst - 1)
	{
		dst[lenghtdst + i] = src[i];
		i++;
	}
	dst[lenghtdst + i] = '\0';
	return (lenghtdst + ft_strlen(src));
}
