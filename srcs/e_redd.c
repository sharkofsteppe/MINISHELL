/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:01:27 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/26 14:06:15 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	reddirection(char **rdr, t_shell *shell)
{
	int		fd[2];
	int		flag;
	int		i;

	if (!rdr)
		return ;
	i = -1;
	while (rdr[++i] != NULL)
	{
		if (rdr[i][0] == '>' && rdr[i][1] == '>')
			flag = 1;
		if (rdr[i][0] == '>' && rdr[i][1] == '\0')
			flag = 1;
		if (rdr[i][0] == '<' && rdr[i][1] == '\0')
			flag = 1;
	}
}
