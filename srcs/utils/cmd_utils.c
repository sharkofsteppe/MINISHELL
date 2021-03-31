/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:45:39 by ezachari          #+#    #+#             */
/*   Updated: 2021/03/31 18:57:52 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_bin_err(char **split, char *line)
{
	free_split(split);
	free(line);
	print_error("minibash: ", 0, 0, 1);
	return (NULL);
}

char	*search_bin(char *bin, t_shell *shell)
{
	t_bin			d;
	int				i;

	i = -1;
	if ((d.path = get_env("PATH", shell)) == NULL)
		return (NULL);
	d.res = NULL;
	d.search = ft_split(d.path, ':');
	while (d.search[++i] != NULL)
	{
		d.newpath = ft_strjoin(d.search[i], "/");
		if ((d.dir = opendir(d.newpath)) == NULL)
			return (search_bin_err(d.search, d.newpath));
		while ((d.info = readdir(d.dir)) != NULL)
			if (ft_strncmp(d.info->d_name, bin, ft_strlen(bin) + 1) == 0)
				d.res = ft_strjoin(d.newpath, bin);
		free(d.newpath);
		closedir(d.dir);
	}
	free_split(d.search);
	return (d.res);
}
