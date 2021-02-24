/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:48 by gesperan          #+#    #+#             */
/*   Updated: 2021/02/24 19:43:18 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_all all;
	char *line;
	
	all.env = env;
	all.home = get_env("HOME", all.env);
	while (1)
	{
		print_promt(&all);
		get_next_line(0, &line);
		all.cmd = ft_split(line, ';');
		free(line);
		exec_cmd(&all);
		free_split(all.cmd);
	}
	return (0);
}
