/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:48:18 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 14:53:11 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_split(char **split)
{
	int i;

	i = -1;
	if (!split)
		return ;
	while (split[++i] != NULL)
	{
		if (split[i])
		{
			free(split[i]);
			split[i] = NULL;
		}
	}
	free(split);
	split = NULL;
}
