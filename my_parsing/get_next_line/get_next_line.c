/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <ameskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:49 by ameskine          #+#    #+#             */
/*   Updated: 2025/12/06 17:52:28 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

static char	*get_next(char *buffer)
{
	char	*line;
	size_t	len;
	char	*temp;
	size_t	i;

	if (!buffer)
		return (NULL);
	temp = ft_strchr(buffer, '\n');
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	len = ft_strlen(temp) - 1;
	line = ft_calloc(len + 1, 1);
	i = 0;
	while (i < len)
	{
		line[i] = temp[i + 1];
		i++;
	}
	line[i] = '\0';
	free(buffer);
	return (line);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

static char	*read_line(char *res, int fd)
{
	char	*buffer;
	int		read_fd;
	char	*tmp;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (check_new_line(res) == 0)
	{
		read_fd = read(fd, buffer, BUFFER_SIZE);
		if (read_fd == -1)
			return (free(res), free(buffer), NULL);
		if (read_fd == 0)
			break ;
		buffer[read_fd] = '\0';
		tmp = res;
		res = ft_strjoin(res, buffer);
		free(tmp);
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(buffer, fd);
	if (!buffer)
		return (NULL);
	next_line = get_line(buffer);
	buffer = get_next(buffer);
	return (next_line);
}
