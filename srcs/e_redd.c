/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:01:27 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/20 19:15:41 by ezachari         ###   ########.fr       */
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
	// i = -1;
	// while (in != NULL)
	// {
	// 	if ((fd[0] = open(in[++i], O_RDONLY, 0644)) == -1)
	// 		set_status(1);
	// 	if ((dup2(fd[0], STDIN_FILENO)) == -1)
	// 	{
	// 		close(fd[0]);
	// 		set_status(1);
	// 	}
	// 	close(fd[0]);
	// }
	// while (out != NULL)
	// {
	// 	if ((fd[1] = open(out[++i], O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	// 		set_status(1);
	// 	if ((dup2(fd[1], STDOUT_FILENO)) == -1)
	// 	{
	// 		close(fd[1]);
	// 		set_status(1);
	// 	}
	// 	close(fd[1]);
	// }
