/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:06:54 by ezachari          #+#    #+#             */
/*   Updated: 2021/04/02 16:42:59 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hist_dup(char *new, t_shell *shell)
{
	shell->h_ind++;
	return (ft_strdup(new));
}

char	**history_add(char **old, char *new_line, t_shell *shell)
{
	char	**new;
	int		count;
	int		i;

	i = -1;
	count = get_argv_size(old);
	if (!(new = (char **)ft_calloc(count + 2, sizeof(char *))))
		return (NULL);
	if (count == 0)
	{
		new[++i] = ft_strdup(new_line);
		shell->h_ind++;
	}
	else
	{
		while (++i < count)
		{
			new[i] = ft_strdup(old[i]);
			shell->h_ind++;
		}
		if (ft_strncmp(new[i - 1], new_line, ft_strlen(new_line) + 1) != 0)
			new[i] = hist_dup(new_line, shell);
	}
	return (new);
}

void	add_to_history(char *line, t_shell *shell)
{
	char	**old;

	shell->h_ind = 0;
	if (line[0] == '\0')
		return ;
	if (!shell->history)
		shell->history = (char **)ft_calloc(1, sizeof(char *));
	old = shell->history;
	shell->history = history_add(shell->history, line, shell);
	free_split(old);
}
