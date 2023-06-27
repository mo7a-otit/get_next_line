/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:47:53 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/25 22:45:16 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str, int i)
{
	char	*m;

	if (!str)
		return (0);
	if (str[0] == 0)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	m = (char *)malloc(i + 2);
	if (!m)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		m[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		m[i] = '\n';
		i++;
	}
	m[i] = '\0';
	return (m);
}

char	*get_next(char *save)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == 0)
	{
		free (save);
		return (NULL);
	}
	next = (char *)malloc(ft_strlen(save) - i + 1);
	if (!next)
		return (NULL);
	if (save[i] == '\n')
		i++;
	j = 0;
	while (save[i])
		next[j++] = save[i++];
	next[j] = '\0';
	free(save);
	return (next);
}

char	*ft_read(int fd, char *save)
{
	char	*buf;
	int		bytes;

	buf = (char *)malloc((BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (!save)
	{
		save = malloc(1);
		save[0] = 0;
	}
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free (save), free (buf), NULL);
		buf[bytes] = '\0';
		save = ft_strjoin(save, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free (buf);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[10240];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (0);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (0);
	line = ft_get_line (save[fd], 0);
	save[fd] = get_next (save[fd]);
	return (line);
}
