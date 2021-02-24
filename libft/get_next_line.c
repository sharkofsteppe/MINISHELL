/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:55:47 by gesperan          #+#    #+#             */
/*   Updated: 2021/01/07 18:29:57 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		error_exit(char **buffer, char **line)
{
	free(*line);
	*line = NULL;
	free(*buffer);
	*buffer = NULL;
	return (ERROR);
}

static int		cutndwrite(char **buffer, char **line, int length)
{
	int		index;
	char	*leakprevention;

	(*buffer)[length] = END_STRING;
	index = finder(*buffer, NEW_LINER);
	if (index != FALSE)
	{
		leakprevention = *line;
		if (!(*line = ft_strjoin(*line, *buffer)))
			return (error_exit(buffer, line));
		free(leakprevention);
		(*line)[finder(*line, NEW_LINER)] = END_STRING;
		leakprevention = *buffer;
		*buffer = ft_strdup(*buffer + index + 1);
		free(leakprevention);
		return (ENDLINE_TOUCHED);
	}
	leakprevention = *line;
	if (!(*line = ft_strjoin(*line, *buffer)))
		return (error_exit(buffer, line));
	free(leakprevention);
	leakprevention = NULL;
	return (ENDLINE_NOT_FOUND);
}

int				get_next_line(int fd, char **line)
{
	static char *buff = NULL;
	char		buffer_check[1];
	int			value;
	int			length;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buffer_check, 0) < 0)
		return (ERROR);
	if (!(*line = ft_strdup("")))
		return (ERROR);
	if (buff)
		if ((value = cutndwrite(&buff, line, ft_strlen(buff))) != 0)
			return (value);
	free(buff);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (error_exit(&buff, line));
	while ((length = read(fd, buff, BUFFER_SIZE)) > 0)
		if ((value = cutndwrite(&buff, line, length)) != 0)
			return (value);
	free(buff);
	buff = NULL;
	if (length != BUFFER_SIZE)
		return (EOF_REACHED);
	return (0);
}
