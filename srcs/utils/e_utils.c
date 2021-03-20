/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:06:37 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 16:06:28 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_argv_size(char **argv)
{
	int i;

	if (argv == NULL)
		return (0);
	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}
